#include <source/sfml_facades/screen.h>
#include <source/utility/vector2d.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/image.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/drawable_objects/clickable_object.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma once

class EntityInfoInterface : public DrawableObjectsGroup, public ClickableObject {
    RoundedRectangle background_;
    Image entity_image_;
    Text entity_name_;
    Text entity_info_;
public:
    explicit EntityInfoInterface(const Screen& screen);
    void update(const json&, const Color&);
    EntityInfoInterface& operator=(const EntityInfoInterface&) = delete;
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
};