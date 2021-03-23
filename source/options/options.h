#include <SFML/Graphics.hpp>
#include <source/geometry/point.h>

#ifndef DIPLOMACY_OPTIONS_H
#define DIPLOMACY_OPTIONS_H
struct GameOptions {
    GameOptions();
    float hexagon_radius;
    float hexagon_rotation;
    Point hexagon_offset;
    sf::Color neutral_player_color;
    sf::Color hexagon_outline_color;
    float hexagon_outline_thickness;
};
#endif //DIPLOMACY_OPTIONS_H
