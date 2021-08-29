#include <source/options/options.h>
#include <cmath>

GameOptions::GameOptions() : neutral_player_index(0), hexagon_options(Color(0, 0, 0)),
    hexagon_offset(Vector2D(hexagon_options.radius * 1.5f, hexagon_options.radius * static_cast<float>(sqrt(3)) / 2)),
    image_size_(hexagon_options.radius * 1.6f, hexagon_options.radius * 1.6f),
    draw_offset(3 * hexagon_options.radius, 2 * hexagon_options.radius) {}

ObjectSize GameOptions::get_image_size() const {
    return image_size_;
}

Vector2D GameOptions::get_image_offset() const {
    return {0, 0};
}
