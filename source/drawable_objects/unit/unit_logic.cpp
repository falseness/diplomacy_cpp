#include <deque>
#include "unit_logic.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects/unit/unit.h>
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>


ClickResponse UnitLogic::ClickLogic(const Unit& unit, Grid& grid, std::pair<int, int> coord) {
    if (coord == unit.get_coord()) {
        return {true, false, true};
    }
    if (!grid.logic_helper_.is_visited(coord)) {
        return {true, true, false};
    }
    unit.MoveTo(grid, coord);

    return {!unit.get_moves(), false, false};
}

void UnitLogic::Select(const SceneInfo& scene, const Unit& unit) {
    const Grid& grid = scene.grid;

    std::vector<std::pair<int, int>> visited_coords;

    std::deque<std::pair<int, int>> coords;

    visited_coords.push_back(unit.get_coord());

    coords.push_back(unit.get_coord());

    grid.logic_helper_.increment_counter();
    grid.logic_helper_.visit(coords.front());
    grid.logic_helper_.set_info(coords.front(), 0);
    grid.logic_helper_.set_parent(coords.front(), coords.front());

    const unsigned int max_moves = unit.is_my_turn() ? unit.get_moves() : unit.get_speed();

    while (!coords.empty()) {
        std::pair<int, int> coord = coords.front();
        coords.pop_front();
        int moves_count = grid.logic_helper_.get_info(coord);
        if (moves_count + 1 > max_moves)
            continue;
        auto neighbours = grid.get_neighbours(coord);
        for (auto new_coord : neighbours) {
            if (grid.is_coord_out_of_range(new_coord) || grid.logic_helper_.is_visited(new_coord))
                continue;

            if (!grid.get_cell(new_coord)->is_passable() && !grid.get_cell(new_coord)->is_hittable()) {
                continue;
            }
            grid.logic_helper_.visit(new_coord);
            visited_coords.push_back(new_coord);
            grid.logic_helper_.set_parent(new_coord, coord);

            if (grid.get_cell(new_coord)->is_hittable())
                grid.logic_helper_.set_info(new_coord, static_cast<int>(max_moves));
            else {
                grid.logic_helper_.set_info(new_coord, moves_count + 1);
                coords.push_back(new_coord);
            }
        }
    }
    scene.selection_border.UpdateBorder(visited_coords);
}
