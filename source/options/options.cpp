#include <source/options/options.h>
#include <cmath>

GameOptions::GameOptions() {
    hexagon_radius = 50.f;
    hexagon_rotation = 90.f;
    hexagon_offset = Point(hexagon_radius * 1.5, hexagon_radius * sqrt(3) / 2);
    neutral_player_color = sf::Color(208, 208, 208);
    hexagon_outline_color = sf::Color(0, 0, 0);
    hexagon_outline_thickness = 0.05 * hexagon_radius;
}
