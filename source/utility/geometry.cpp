#include "geometry.h"
#include <cmath>

float Geometry::PythagoreanSquared(float x, float y) {
    return x * x + y * y;
}

float Geometry::RadiansToDegrees(float radians) {
    return radians / kPi * 180;
}

const float Geometry::kPi = acosf(-1);
