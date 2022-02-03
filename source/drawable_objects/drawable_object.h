#include <source/sfml_facades/screen.h>
#include "source/options/game.h"

#pragma once

class DrawableObject {
public:
    virtual void Draw(Screen&, const GameOptions&) = 0;
    virtual ~DrawableObject() = default;
};
