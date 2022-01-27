#include <source/utility/color.h>
#include <array>
#pragma once

struct RoundedRectangle {
    Color border_color = Color(0, 0, 0);
    // width 0 means no border
    float border_width = 5;
    Color background_color = Color(255, 0, 0);
    float left_side_x = 0;
    float up_side_y = 0;
    float width = 100;
    float height = 400;
    // radius 0 means no circle
    float corner_radius = 30;
    float get_right() const;
    float get_left() const;
    float get_up() const;
    float get_bottom() const;
};
