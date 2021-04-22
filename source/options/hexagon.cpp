#include "hexagon.h"

HexagonOptions::HexagonOptions(const Color& main_color) : radius(75.f), rotation(90.f), fill_color(main_color),
    outline_color(Color(0, 0, 0)), outline_thickness(0.05f * radius) {}