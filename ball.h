#ifndef BALL_H
#define BALL_H

#include "vector.h"

class Ball {
    private:
        Vector pos, vel;
        double radius, elasticity;

    public:
        void handle_collision(Ball other);
        void handle_collision(Rectangle bounds);
};

#endif