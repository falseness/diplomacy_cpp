#include "vector2d.h"

Vector2D::Vector2D(float init_x, float init_y) : x(init_x), y(init_y) {}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D operator+(const Vector2D& vector1, const Vector2D& vector2) {
    Vector2D result(vector1);
    result += vector2;
    return result;
}

Vector2D operator-(const Vector2D& vector1, const Vector2D& vector2) {
    Vector2D result(vector1);
    result -= vector2;
    return result;
}
