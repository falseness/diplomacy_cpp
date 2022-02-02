#include <deque>
#include <tuple>
#include "unit_logic.h"
#include <source/drawable_objects/unit/unit.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <iostream>

ClickResponse UnitLogic::ClickLogic(Unit& unit, Grid& grid, std::pair<int, int> coord) {
    if (coord == unit.get_coord()) {
        return {true, false, true};
    }
    if (!grid.logic_helper_.is_visited(coord)) {
        return {true, true, false};
    }
    unit.MoveTo(grid, coord);

    return {!unit.get_moves(), false, false};
}

void UnitLogic::Select(Unit& unit, Grid& grid) {
    std::deque<std::pair<int, int>> coords;
    coords.push_back(unit.get_coord());

    grid.logic_helper_.increment_counter();
    grid.logic_helper_.visit(coords.front());
    grid.logic_helper_.set_info(coords.front(), 0);
    grid.logic_helper_.set_parent(coords.front(), coords.front());

    while (!coords.empty()) {
        std::pair<int, int> coord = coords.front();
        coords.pop_front();
        int moves_count = grid.logic_helper_.get_info(coord);
        if (moves_count + 1 > unit.get_moves())
            continue;
        auto neighbours = grid.get_neighbours(coord);
        for (auto new_coord : neighbours) {
            if (grid.logic_helper_.is_visited(new_coord) || !grid.get_cell(new_coord)->is_passable())
                continue;
            grid.logic_helper_.visit(new_coord);
            grid.logic_helper_.set_info(new_coord, moves_count + 1);
            grid.logic_helper_.set_parent(new_coord, coord);
            coords.push_back(new_coord);
        }
    }
}
