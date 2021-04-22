#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include <source/drawable_objects/cell/cell.h>
#include <source/options/options.h>
#include <source/player/player.h>
#include <vector>

#pragma once

class Grid : public DrawableObjectsGroup {
    std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
    const Entity* selected_entity_;
public:
    Grid(const std::vector<Player>&);
    void HandleClick(const Vector2D&, const GameOptions&);
};
