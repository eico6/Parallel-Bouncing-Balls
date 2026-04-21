#pragma once
#include <cmath>
#include <string>

struct Vector {
    double x, y;

    Vector(double x = 0, double y = 0) : x(x), y(y) {}

    // --- Getters / Setters ---
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x_) { x = x_; }
    void setY(double y_) { y = y_; }

    Vector& set(double x_, double y_) { x = x_; y = y_; return *this; }

    // --- Static (new Vector) ---
    static Vector add(const Vector& a, const Vector& b) { return {a.x + b.x, a.y + b.y}; }
    static Vector sub(const Vector& a, const Vector& b) { return {a.x - b.x, a.y - b.y}; }
    static Vector scale(const Vector& v, double s) { return {v.x * s, v.y * s}; }
    static Vector div(const Vector& v, double d) { return {v.x / d, v.y / d}; }

    // --- Instance ---
    Vector add(double dx, double dy) const { return {x + dx, y + dy}; }
    Vector add(const Vector& v) const { return {x + v.x, y + v.y}; }

    Vector sub(double dx, double dy) const { return {x - dx, y - dy}; }
    Vector sub(const Vector& v) const { return {x - v.x, y - v.y}; }

    Vector scale(double s) const { return {x * s, y * s}; }
    Vector div(double d) const { return {x / d, y / d}; }

    Vector nor() const {
        double l = std::sqrt(x * x + y * y);
        return {x / l, y / l};
    }

    Vector reverse() const { return {-x, -y}; }

    static double len(double x, double y) { return std::sqrt(x * x + y * y); }
    double len() const { return std::sqrt(x * x + y * y); }

    static double len2(double x, double y) { return x * x + y * y; }
    double len2() const { return x * x + y * y; }

    static double distance(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1, dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }
    double distance(const Vector& v) const {
        double dx = v.x - x, dy = v.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }
    double distance2(const Vector& v) const {
        double dx = v.x - x, dy = v.y - y;
        return dx * dx + dy * dy;
    }

    static double dot(double x1, double y1, double x2, double y2) { return x1 * x2 + y1 * y2; }
    double dot(double dx, double dy) const { return x * dx + y * dy; }
    double dot(const Vector& v) const { return x * v.x + y * v.y; }

    bool isZero() const { return x == 0 && y == 0; }

    bool operator==(const Vector& v) const { return x == v.x && y == v.y; }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};
