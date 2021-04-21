#include <source/options/options.h>
#include <cmath>

GameOptions::GameOptions() : neutral_player_color(Color(208, 208, 208)), hexagon_options(neutral_player_color),
    hexagon_offset(Point(hexagon_options.radius * 1.5, hexagon_options.radius * sqrt(3) / 2)) {}
