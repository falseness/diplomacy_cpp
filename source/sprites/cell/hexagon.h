#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

class Cell;

#pragma once

class Hexagon : public Sprite {
    const Cell& cell_;
public:
    Hexagon(const Cell&);
    void Draw(Screen&, const GameOptions&);
};
