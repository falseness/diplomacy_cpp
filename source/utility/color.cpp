#include "color.h"

Color::Color(uint8_t red_color_value, uint8_t green_color_value, uint8_t blue_color_value) :
    red(red_color_value), green(green_color_value), blue(blue_color_value) {}

const Color Color::kWhite(255, 255, 255);