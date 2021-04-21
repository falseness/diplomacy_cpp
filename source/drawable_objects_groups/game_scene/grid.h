#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include <source/drawable_objects/cell/cell.h>
#include <source/options/options.h>
#include <vector>

#pragma once

class Grid : public DrawableObjectsGroup {
    std::vector<std::vector<unique_ptr<Cell>>> cells_;
public:
    Grid(const GameOptions&);
};
