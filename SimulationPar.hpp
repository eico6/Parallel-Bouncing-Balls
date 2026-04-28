#pragma once
#include "Ball.hpp"
#include "Grid.hpp"
#include "Simulation.hpp"
#include <omp.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class SimulationPar : public Simulation {
public:
    const double gravity;
    const Rect bounds;
    std::vector<Ball>& balls;
    Grid& grid;

    double clearTime, addToGridTime, collisionTime;

    SimulationPar(double gravity, Rect bounds,
                  std::vector<Ball>& balls,
                  Grid& grid)
        : gravity(gravity), bounds(bounds), balls(balls), grid(grid)
    {
        for (auto& kv : grid){
            cellLists.push_back(&kv.second);
        }

        ballLocks.reserve(balls.size());
        checkedPairs.reserve(balls.size());
        for (int i = 0; i < balls.size(); i++){
            Ball& a = balls[i];

            omp_lock_t *lock = new omp_lock_t;
            omp_init_lock(lock);
            ballLocks.push_back(lock);
            
            checkedPairs.push_back(new std::unordered_set<Ball*>);
        }
        
        for(const CellKey& cell : grid.getCells(bounds)){
            omp_lock_t *lock = new omp_lock_t;
            omp_init_lock(lock);
            locks[cell] = lock;
        }
    }

    void update() {
        clearTime = omp_get_wtime();
        #pragma omp parallel for
        for (std::vector<Ball*>* list : cellLists) {
            list->clear();
        }
        #pragma omp parallel for
        for (std::unordered_set<Ball*>* set : checkedPairs) {
            set->clear();
        }
        clearTime = omp_get_wtime() - clearTime;

        addToGridTime = omp_get_wtime();
        #pragma omp parallel for
        for (Ball& b : balls){
            b.velocity = b.velocity.add(0, gravity / FPS);
            b.position = b.position.add(Vector::div(b.velocity, FPS));
            
            resolveWallCollision(b);
            
            addToGrid(b);
        }
        addToGridTime = omp_get_wtime() - addToGridTime;
        
        collisionTime = omp_get_wtime();
        #pragma omp parallel for
        for (std::vector<Ball*>* list : cellLists) {
            for (int i = 0; i < (int)list->size(); i++) {
                Ball* a = list->at(i);
                for (int j = i+1; j < (int)list->size(); j++) {
                    Ball* b = list->at(j);
                    if (a->overlaps(*b)) {
                        omp_lock_t* lockA = ballLocks[a->id];
                        omp_lock_t* lockB = ballLocks[b->id];

                        omp_set_lock(lockA);
                        omp_set_lock(lockB);
                        
                        if (!checkedPairs[a->id]->count(b)){
                            checkedPairs[a->id]->insert(b);
                            checkedPairs[b->id]->insert(a);
                            resolveOverlap(*a, *b);
                            resolveCollision(*a, *b);
                        }
                        
                        omp_unset_lock(lockA);
                        omp_unset_lock(lockB);
                    }
                }
            }
        }
        collisionTime = omp_get_wtime() - collisionTime;
    }

    const Rect& getBounds() const override { return bounds; }
    std::vector<Ball>& getBalls() override { return balls; }
    const Grid& getGrid() const override { return grid; }

private:
    std::unordered_map<CellKey, omp_lock_t*, CellKeyHash> locks;

    std::vector<std::unordered_set<Ball*>*> checkedPairs;
    std::vector<omp_lock_t*> ballLocks;

    std::vector<std::vector<Ball*>*> cellLists;

    void addToGrid(Ball& b) {
        Rect ballBounds = {
            b.position.x - b.radius,
            b.position.y - b.radius,
            2 * b.radius,
            2 * b.radius
        };
        for (const CellKey& cell : grid.getCells(ballBounds)) {
            auto it = locks.find(cell);
            
            omp_set_lock(it->second);
            grid.get(cell)->push_back(&b);
            omp_unset_lock(it->second);
        }
    }

    void resolveWallCollision(Ball& b) {
        // Left wall
        if (b.position.x - b.radius < bounds.getX()) {
            b.position.setX(bounds.getX() + b.radius);
            b.velocity.setX(-b.velocity.getX());
        }
        // Right wall
        if (b.position.x + b.radius > bounds.getMaxX()) {
            b.position.setX(bounds.getMaxX() - b.radius);
            b.velocity.setX(-b.velocity.getX());
        }
        // Top wall (y min)
        if (b.position.y - b.radius < bounds.getY()) {
            b.position.setY(bounds.getY() + b.radius);
            b.velocity.setY(-b.velocity.getY());
        }
        // Bottom wall (y max)
        if (b.position.y + b.radius > bounds.getMaxY()) {
            b.position.setY(bounds.getMaxY() - b.radius);
            b.velocity.setY(-b.velocity.getY());
        }
    }

    void resolveCollision(Ball& a, Ball& b) {
        Vector AB = a.position.sub(b.position);
        if (AB.isZero()) return;

        Vector vAB = a.velocity.sub(b.velocity);

        double scalar = 2.0 / (a.mass + b.mass)
                        * b.mass
                        * vAB.dot(AB)
                        / AB.dot(AB);

        Vector impulse = AB.scale(scalar);

        a.velocity = a.velocity.sub(impulse);
        b.velocity = b.velocity.add(impulse);
    }

    void resolveOverlap(Ball& a, Ball& b) {
        Vector AB = a.position.sub(b.position);
        if (AB.isZero()){
            return;
        } 

        double dist = AB.len();
        double overlap = a.radius + b.radius - dist;
        if (overlap <= 0){
            return;
        }

        Vector normal = AB.div(dist);
        normal = normal.scale(overlap / (a.mass + b.mass));

        a.position = a.position.add(normal.scale(b.mass));
        b.position = b.position.sub(normal.scale(a.mass));
    }
};
