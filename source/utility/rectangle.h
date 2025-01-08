#pragma once

#include "source/utility/vector2d.h"


struct Rectangle {
    float left_side_x;
    float up_side_y;
    float width;
    float height;

    [[nodiscard]] float get_right() const {
        return left_side_x + width;
    }
    [[nodiscard]] float get_left() const {
        return left_side_x;
    }
    [[nodiscard]] float get_up() const {
        return up_side_y;
    }
    [[nodiscard]] float get_bottom() const {
        return up_side_y + height;
    }

    // top means minimum_y
    inline Vector2D top_left_corner() const {
        return {get_left(), get_up()};
    }

    inline Vector2D top_right_corner() const {
        return {get_right(), get_up()};
    }

    inline Vector2D bottom_right_corner() const {
        return {get_right(), get_bottom()};
    }

    inline Vector2D bottom_left_corner() const {
        return {get_left(), get_bottom()};
    }

    void set_center_x(float center_x) {
        left_side_x = center_x - width / 2;
    }

    void set_center_y(float center_y) {
        up_side_y = center_y - height / 2;
    }

    void set_center(const Vector2D& center) {
        set_center_x(center.x);
        set_center_y(center.y);
    }

    float get_center_y() const {
        return (get_bottom() + get_up()) / 2;
    }

    float get_center_x() const {
        return (get_left() + get_right()) / 2;
    }

    Vector2D get_center() const {
        return {get_center_x(), get_center_y()};
    }

    static constexpr size_t kRectangleVerticesCount = 4;
    std::array<Vector2D, kRectangleVerticesCount> get_points() const {
        return {top_left_corner(), top_right_corner(), bottom_right_corner(), bottom_left_corner()};
    }

    [[nodiscard]] bool is_inside(const Vector2D& pos) const {
        return get_left() <= pos.x && pos.x <= get_right() &&
            get_up() <= pos.y && pos.y <= get_bottom();
    }


    void set_top_left_corner_pos(const Vector2D& position) {
        left_side_x = position.x;
        up_side_y = position.y;
    }
    void move_by(const Vector2D& transition) {
        left_side_x += transition.x;
        up_side_y += transition.y;
    }
};
