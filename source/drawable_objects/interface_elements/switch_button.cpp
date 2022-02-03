//
// Created by nikita on 03.02.2022.
//

#include "switch_button.h"

void SwitchButton::update_texts_position(Screen &screen) {
    left_text.set_center(get_center() - Vector2D(width / 4, 0), screen);
    right_text.set_center(get_center() + Vector2D(width / 4, 0), screen);
}

void SwitchButton::Draw(Screen& screen, const GameOptions& game_options) {
    RoundedRectangle::Draw(screen, game_options);
    screen.DrawVerticalLine(get_center_x(), get_bottom(), get_up(), border_width, border_color);
    update_texts_position(screen);
    left_text.Draw(screen, game_options);
    right_text.Draw(screen, game_options);
}

void SwitchButton::do_switch() {
    std::swap(left_text.color, right_text.color);
    is_left_selected = !is_left_selected;
}

Text& SwitchButton::get_selected_text() {
    if (is_left_selected)
        return left_text;
    return right_text;
}

void SwitchButton::set_text_size(size_t text_size) {
    left_text.size = right_text.size = text_size;
}
