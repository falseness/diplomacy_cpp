#include <source/utility/color.h>
#include <source/utility/point.h>
#include <source/options/hexagon.h>

#pragma once

struct GameOptions {
    std::size_t neutral_player_index;
    HexagonOptions hexagon_options;
    Point hexagon_offset;
    GameOptions();
};
