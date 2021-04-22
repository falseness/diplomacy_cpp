#include <source/utility/color.h>
#include <source/utility/point.h>
#include <source/utility/object_size.h>
#include <source/options/hexagon.h>

#pragma once

struct GameOptions {
    std::size_t neutral_player_index;
    HexagonOptions hexagon_options;
    Point hexagon_offset;
private:
    ObjectSize image_size_;
public:
    ObjectSize get_image_size() const;
    Point get_image_offset() const;
    GameOptions();
};
