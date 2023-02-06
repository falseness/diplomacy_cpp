#include <source/utility/color.h>
#include <source/utility/vector2d.h>
#include <source/utility/object_size.h>
#include <source/options/hexagon.h>

#pragma once

struct GameOptions {
    std::size_t neutral_player_index;
    HexagonOptions hexagon_options;
    Vector2D hexagon_offset;
private:
    ObjectSize image_size_;
public:
    static constexpr std::size_t kMaxFPS = 120;
    ObjectSize get_image_size() const;
    Vector2D get_image_offset() const;
    Vector2D draw_offset;
    GameOptions();
};
