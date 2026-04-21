#pragma once
#include "Vector.hpp"
#include "Constants.hpp"

struct Ball {
    static int nextID;
    int id;
    Vector position;
    Vector velocity;
    const double radius;
    const double mass;
    const double elasticity;

    Ball(double x, double y, double radius, double elasticity)
        : id(nextID++),
          position(x, y),
          velocity(0, 0),
          radius(radius),
          mass(radius * radius),
          elasticity(elasticity) {}

    void update() {
        position = position.add(velocity.scale(1.0 / FPS));
    }

    bool overlaps(const Ball& other) const {
        double dx = position.x - other.position.x;
        double dy = position.y - other.position.y;
        double rSum = radius + other.radius;
        return dx * dx + dy * dy <= rSum * rSum;
    }
};

int Ball::nextID = 0;
