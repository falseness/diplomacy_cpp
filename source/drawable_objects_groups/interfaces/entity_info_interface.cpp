#include "entity_info_interface.h"

EntityInfoInterface::EntityInfoInterface(const Screen& screen) {
    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = 0.03f * w;

    Vector2D pos(0, h * 0.5f);

    float this_height = h - pos.y;
    float this_width = this_height * 1.7f;



    background_.set_pos(Vector2D(pos.x - corner_radius, pos.y));
    background_.height = this_height + corner_radius;
    background_.width = this_width + corner_radius;
    background_.corner_radius = corner_radius;

    drawable_objects_.push_back(&background_);
}
