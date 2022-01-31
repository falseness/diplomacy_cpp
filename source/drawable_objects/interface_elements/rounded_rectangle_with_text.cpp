//
// Created by nikita on 31.01.2022.
//

#include "rounded_rectangle_with_text.h"

void RoundedRectangleWithText::move_text_to_center(Screen& screen) {
    float x = (get_left() + get_right() - text.get_width(screen)) / 2;
    float y = (get_up() + get_bottom() - text.get_height(screen)) / 2;
    text.position = {x, y};
}

void RoundedRectangleWithText::Draw(Screen& screen, const GameOptions& game_options) {
    RoundedRectangle::Draw(screen, game_options);
    move_text_to_center(screen);
    text.Draw(screen, game_options);
}
