#include "entity_info_interface.h"

EntityInfoInterface::EntityInfoInterface(const Screen& screen) {
    visible_ = false;

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
    background_.background_color = Color(0, 255, 00);

    entity_image_.size = {this_height * 0.775f, this_height * 0.775f};
    entity_image_.position.x = pos.x + this_height * 0.38f;
    entity_image_.position.y = pos.y + this_height * 0.5f;

    entity_name_.position.x = entity_image_.position.x + entity_image_.size.width / 2;
    entity_name_.position.y = pos.y + this_height * 0.02f;
    entity_name_.size = static_cast<size_t>(this_height * 0.2f);

    entity_info_.position.x = entity_name_.position.x;
    entity_info_.position.y = entity_name_.position.y + entity_name_.size;
    entity_info_.size = static_cast<size_t>(this_height * 0.1f);


    drawable_objects_.push_back(&background_);
    drawable_objects_.push_back(&entity_image_);
    drawable_objects_.push_back(&entity_name_);
    drawable_objects_.push_back(&entity_info_);
}
#include <iostream>
void EntityInfoInterface::update(const json& entity) {
    entity_image_.name = entity["name"];
    entity_name_.text = entity["name"];
    //std::vector<std::string> tmp = entity["info"];
    std::string entity_info;
    for (const auto& item : entity["info"].items()) {
        auto tmp = item.value().dump();
        if (tmp.front() == '"' && tmp.back() == '"' && tmp.size() > 1) {
            tmp.erase(tmp.begin());
            tmp.pop_back();
        }
        entity_info += item.key() + ": " + tmp + "\n";
    }

    entity_info_.text = entity_info;
}
