#include <source/utility/color.h>
#include <source/utility/point.h>
#include <source/options/hexagon.h>

#pragma once

struct GameOptions {
    Color neutral_player_color;
    HexagonOptions hexagon_options;
    Point hexagon_offset;
    GameOptions();
};
