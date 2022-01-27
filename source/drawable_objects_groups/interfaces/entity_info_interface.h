#include "source/sfml_facades/screen.h"
#include "source/utility/vector2d.h"
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>

#pragma once

class EntityInfoInterface : public DrawableObjectsGroup {
    RoundedRectangle background_;

public:
    explicit EntityInfoInterface(const Screen& screen);
};