#include "game.h"
#include <cmath>

GameOptions::GameOptions(const float radius) : hexagon_options(radius, Color(0, 0, 0)),
        hexagon_offset(Vector2D(hexagon_options.radius * 1.5f, hexagon_options.radius * sqrtf(3) / 2)),
        image_size_(hexagon_options.radius * 1.6f, hexagon_options.radius * 1.6f),
        draw_offset(3 * hexagon_options.radius, 2 * hexagon_options.radius),
        text_size_(static_cast<size_t>(hexagon_options.radius * 0.7f)),
        text_offset_(0, hexagon_options.radius * 0.1f), text_outline_thickness(hexagon_options.radius * 0.05f) {
    hexagon_offset += {hexagon_options.outline_thickness * 1.5f / 2,
                       hexagon_options.outline_thickness * sqrtf(3) / 2 / 2};
}

void GameOptions::ScaleRadius(const float dt) {
    *this = GameOptions(hexagon_options.radius + dt);
}