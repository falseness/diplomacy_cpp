#pragma once

struct Vector2D {
    float x;
    float y;
    Vector2D(float, float);
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);
    Vector2D& operator*=(float);
    float get_squared_length() const;
    float get_length() const;
};

Vector2D operator+(const Vector2D&, const Vector2D&);

Vector2D operator-(const Vector2D&, const Vector2D&);

Vector2D operator*(const Vector2D&, float);

float cross_product(const Vector2D&, const Vector2D&);
int get_sign(float);
