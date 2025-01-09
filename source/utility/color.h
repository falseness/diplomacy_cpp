#pragma once

#include <cstdint>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    constexpr Color(uint8_t red_color_value, uint8_t green_color_value, uint8_t blue_color_value) :
            red(red_color_value), green(green_color_value), blue(blue_color_value) {}
    static const Color kWhite;
    //Color(const Color&);
};
