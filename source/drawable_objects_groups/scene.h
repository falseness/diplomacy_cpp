#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#pragma once

class Scene : public DrawableObjectsGroup {
public:
    virtual void LoopIteration(Screen&, const GameOptions&);
    virtual void HandleClick(const Vector2D&, const GameOptions&) = 0;
};
