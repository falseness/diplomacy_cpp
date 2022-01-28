#include <source/drawable_objects/drawable_object.h>
#include <source/utility/object_size.h>
#include <string>

#pragma once

struct Image : public DrawableObject {
    ObjectSize size{100, 100};
    Vector2D position{100, 100};
    std::string name = "debug";
    void Draw(Screen&, const GameOptions&) override;
};