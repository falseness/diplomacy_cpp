#include <source/sfml_facades/screen.h>
#include <source/utility/vector2d.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/image.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <nlohmann/json.hpp>

#pragma once

class ProductionInterface: public DrawableObjectsGroup {
    RoundedRectangle background_;
public:
    explicit ProductionInterface(const Screen& screen);
};