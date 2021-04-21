#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites/cell/cell.h>
#include <source/options/options.h>
#include <vector>

#pragma once

class Grid : public SpritesGroup {
    std::vector<std::vector<unique_ptr<Cell>>> cells_;
public:
    Grid(const GameOptions&);
};
