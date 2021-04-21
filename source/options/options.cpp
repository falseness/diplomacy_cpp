#include <source/options/options.h>
#include <cmath>

GameOptions::GameOptions() : neutral_player_index(0), hexagon_options(Color(0, 0, 0)),
    hexagon_offset(Point(hexagon_options.radius * 1.5, hexagon_options.radius * sqrt(3) / 2)) {}
