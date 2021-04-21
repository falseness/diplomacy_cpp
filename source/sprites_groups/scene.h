#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#pragma once

class Scene : public SpritesGroup {
public:
    virtual void LoopIteration(Screen&, const GameOptions&);
};
