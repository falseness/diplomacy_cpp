//
// Created by nikita on 27.01.2022.
//

#include "rounded_rectangle.h"

float RoundedRectangle::get_right() const {
    return left_side_x + width;
}

float RoundedRectangle::get_left() const {
    return left_side_x;
}

float RoundedRectangle::get_up() const {
    return up_side_y;
}

float RoundedRectangle::get_bottom() const {
    return up_side_y + height;
}

void RoundedRectangle::set_pos(const Vector2D& position) {
    left_side_x = position.x;
    up_side_y = position.y;
}

void RoundedRectangle::Draw(Screen& screen, const GameOptions &) {
    screen.DrawRoundedRectangle(*this);
}

bool RoundedRectangle::is_inside(const Vector2D& pos) const {
    return get_left() <= pos.x && pos.x <= get_right() && get_up() <= pos.y && pos.y <= get_bottom();
}

void RoundedRectangle::add_to_pos(const Vector2D& transition) {
    set_pos(Vector2D(left_side_x, up_side_y) + transition);
}
