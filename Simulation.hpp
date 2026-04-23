#pragma once

class Simulation {
public:
    virtual const Rect& getBounds() const = 0;
    virtual std::vector<Ball>& getBalls() = 0;
    virtual const Grid& getGrid() const = 0;
    virtual ~Simulation() = default;
};