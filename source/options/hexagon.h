#include <source/utility/vector2d.h>
#include <source/utility/color.h>

#pragma once

struct HexagonOptions {
    float radius;
    float rotation;
    Color fill_color;
    Color outline_color;
    float outline_thickness;
    HexagonOptions(const Color&);
};
