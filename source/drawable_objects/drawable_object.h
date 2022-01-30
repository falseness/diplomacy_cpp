#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#pragma once

class DrawableObject {
public:
    virtual void Draw(Screen&, const GameOptions&) = 0;
    virtual ~DrawableObject() = default;
};
