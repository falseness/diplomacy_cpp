#include <source/drawable_objects/drawable_object.h>

#pragma once

struct Triangle : DrawableObject {
    Color border_color = Color(0, 0, 0);
    // width 0 means no border
    float border_width = 5;
    Color background_color = Color(255, 0, 0);
    Vector2D position{100, 100};
    float side = 100.0f;
};