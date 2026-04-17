#include "vector.h"

// // constructors
// Vector::Vector(double x, double y) : x(x), y(y) {}
// Vector::Vector(const Vector& v) : x(v.x), y(v.y) {}

// // modifiers
// Vector& Vector::set(double x_, double y_) {
//     x = x_; y = y_;
//     return *this;
// }

// Vector& Vector::add(double dx, double dy) {
//     x += dx; y += dy;
//     return *this;
// }

// Vector& Vector::add(const Vector& v) {
//     x += v.x; y += v.y;
//     return *this;
// }

// Vector& Vector::sub(double dx, double dy) {
//     x -= dx; y -= dy;
//     return *this;
// }

// Vector& Vector::sub(const Vector& v) {
//     x -= v.x; y -= v.y;
//     return *this;
// }

// Vector& Vector::scale(double s) {
//     x *= s; y *= s;
//     return *this;
// }

// Vector& Vector::nor() {
//     double l = len();
//     x /= l; y /= l;
//     return *this;
// }

// Vector& Vector::rotateDeg(double degrees) {
//     double rad = degrees * 3.1415 / 180.0; // TODO: pi accuracy
//     double c = cos(rad), s = sin(rad);
//     return set(x*c - y*s, x*s + y*c);
// }

// Vector& Vector::reverse() {
//     x *= -1; y *= -1;
//     return *this;
// }

// // length
// double Vector::len(double x, double y) {
//     return std::sqrt(x*x + y*y);
// }

// double Vector::len() const {
//     return std::sqrt(x*x + y*y);
// }

// double Vector::len2(double x, double y) {
//     return x*x + y*y;
// }

// double Vector::len2() const {
//     return x*x + y*y;
// }

// // distance
// double Vector::distance(double x1, double y1, double x2, double y2) {
//     double dx = x2 - x1, dy = y2 - y1;
//     return std::sqrt(dx*dx + dy*dy);
// }

// double Vector::distance(const Vector& v) const {
//     double dx = v.x - x, dy = v.y - y;
//     return std::sqrt(dx*dx + dy*dy);
// }

// double Vector::distance2(const Vector& v) const {
//     double dx = v.x - x, dy = v.y - y;
//     return dx*dx + dy*dy;
// }

// // dot
// double Vector::dot(double x1, double y1, double x2, double y2) {
//     return x1*x2 + y1*y2;
// }

// double Vector::dot(double x_, double y_) const {
//     return x*x_ + y*y_;
// }

// double Vector::dot(const Vector& v) const {
//     return x*v.x + y*v.y;
// }

// // cross
// double Vector::cross(double x1, double y1, double x2, double y2) {
//     return x1*y2 - y1*x2;
// }

// double Vector::cross(double x_, double y_) const {
//     return x*y_ - y*x_;
// }

// double Vector::cross(const Vector& v) const {
//     return x*v.y - v.x*y;
// }

// // utils
// bool Vector::operator==(const Vector& v) const {
//     return x == v.x && y == v.y;
// }

// std::string Vector::toString() const {
//     return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
// }