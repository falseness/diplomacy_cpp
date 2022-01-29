//
// Created by nikita on 29.01.2022.
//

#include "production.h"

ProductionInterface::ProductionInterface(const Screen &screen) {
    visible_ = false;

    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = w * 0.03f * 1.15f;

    Vector2D pos(w * 0.72f, h * 0.01f);

    float this_height = h * 0.4f;
    float this_width = w - pos.x;

    background_.set_pos(Vector2D(pos.x, pos.y));
    background_.height = this_height;
    background_.width = this_width + corner_radius;
    background_.corner_radius = corner_radius;
    background_.background_color = Color(0, 255, 00);

    drawable_objects_.push_back(&background_);


}
