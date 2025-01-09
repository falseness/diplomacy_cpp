#pragma once

#include <source/drawable_objects/interface_elements/rounded_rectangle.h>


void DrawEntityBar(const unsigned int current_value, const unsigned int maximum_value,
                   const Vector2D& position, const Color& presence_color, const Color& absence_color,
                   Screen& screen, const GameOptions& game_options) {
    assert(current_value <= maximum_value);
    if (current_value == maximum_value) {
        // we don't paint full bars because it creates too much image noise
        return;
    }
    // поменяй на COlorRectangle
    RoundedRectangle rectangle;

    rectangle.width = game_options.hexagon_options.radius * 0.15;

    rectangle.height = game_options.hexagon_options.radius * 0.15;
    rectangle.border_width = game_options.hexagon_options.radius * 0.03;

    const unsigned int rects_count = maximum_value;
    float interval_x = game_options.hexagon_options.radius * 0.1;
    float hpBarWidth = rectangle.width * rects_count + interval_x * (rects_count - 1);

    for (int i = 0; i < maximum_value; ++i) {
        rectangle.background_color = i < current_value ? presence_color : absence_color;
        rectangle.set_top_left_corner_pos(position +
                                          Vector2D(-hpBarWidth / 2 + i * rectangle.width + i * interval_x,
                                                   0));
        screen.DrawOnRectangleBuffer(rectangle);
    }
}
