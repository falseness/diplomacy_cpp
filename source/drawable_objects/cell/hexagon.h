#include <source/drawable_objects/drawable_object.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

class Cell;

#pragma once

class Hexagon : public DrawableObject {
    const Cell& cell_;
public:
    explicit Hexagon(const Cell&);
    void Draw(Screen&, const GameOptions&);
};
