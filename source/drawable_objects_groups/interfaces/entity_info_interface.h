#include "source/sfml_facades/screen.h"
#include "source/utility/vector2d.h"
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/image.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma once

class EntityInfoInterface : public DrawableObjectsGroup {
    RoundedRectangle background_;
    Image entity_image_;
    Text entity_name_;
    Text entity_info_;
public:
    explicit EntityInfoInterface(const Screen& screen);
    void update(const json&);
    EntityInfoInterface& operator=(const EntityInfoInterface&) = delete;
};