#include <source/drawable_objects/drawable_object.h>
#include <source/utility/vector2d.h>
#include <source/utility/color.h>
#include <array>


#pragma once

struct RoundedRectangle : DrawableObject {
    Color border_color = Color(0, 0, 0);
    // width 0 means no border
    float border_width = 5;
    Color background_color = Color(255, 0, 0);
    float left_side_x = 0;
    float up_side_y = 0;
    float width = 100;
    float height = 400;
    // radius 0 means no circle
    float corner_radius = 30;
    void set_pos(const Vector2D&);
    [[nodiscard]] float get_right() const;
    [[nodiscard]] float get_left() const;
    [[nodiscard]] float get_up() const;
    [[nodiscard]] float get_bottom() const;
    void Draw(Screen&, const GameOptions&) override;
    // check if point in rectangle
    [[nodiscard]] bool is_inside(const Vector2D&) const;
};
