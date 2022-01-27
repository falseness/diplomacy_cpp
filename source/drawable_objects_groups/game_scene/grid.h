#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include <source/drawable_objects/cell/cell.h>
#include <source/options/options.h>
#include <source/player/player.h>
#include <vector>
#include <tuple>
#include "grid_logic_helper.h"

#pragma once

class Grid : public DrawableObjectsGroup {
    std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
    Entity* selected_entity_;
    static const size_t kGridRowsCount;
    static const size_t kGridColumnsCount;
public:
    std::vector<std::pair<int, int>> get_neighbours(std::pair<int, int> coord);
    GridLogicHelper logic_helper_;
    Grid(const std::vector<Player>&);
    void HandleClick(const Vector2D&, const GameOptions&);
    void MoveUnit(std::pair<int, int> from, std::pair<int, int> to);
    size_t get_rows_count();
    size_t get_columns_count();
};



