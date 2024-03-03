#include "hexagon.h"


HexagonOptions::HexagonOptions(const float radius, const Color& main_color) : radius(radius), rotation(90.f),
    fill_color(main_color), outline_color(Color(0, 0, 0)), outline_thickness(0.05f * radius) {}