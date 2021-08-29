#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#pragma once

class DrawableObject {
public:
    //virtual void HandleEvent(const sf::Event&) = 0;
    virtual void Draw(Screen&, const GameOptions&) = 0;
};
