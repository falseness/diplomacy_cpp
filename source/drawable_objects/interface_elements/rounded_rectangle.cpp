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

float RoundedRectangle::get_center_y() const {
    return (get_bottom() + get_up()) / 2;
}

float RoundedRectangle::get_center_x() const {
    return (get_left() + get_right()) / 2;
}

Vector2D RoundedRectangle::get_center() const {
    return {get_center_x(), get_center_y()};
}

void RoundedRectangle::set_center_x(float center_x) {
    left_side_x = center_x - width / 2;
}

void RoundedRectangle::set_center_y(float center_y) {
    up_side_y = center_y - height / 2;
}
