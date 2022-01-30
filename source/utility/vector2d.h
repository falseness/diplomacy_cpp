#pragma once

struct Vector2D {
    float x;
    float y;
    Vector2D(float, float);
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);
};

Vector2D operator+(const Vector2D&, const Vector2D&);

Vector2D operator-(const Vector2D&, const Vector2D&);

float cross_product(const Vector2D&, const Vector2D&);
int get_sign(float);
