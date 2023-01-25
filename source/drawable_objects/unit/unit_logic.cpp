#include <deque>
#include "unit_logic.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects/unit/unit.h>
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid_logic_helper.h"

const UnitLogic UnitLogic::kUnitLogic = UnitLogic();


ClickResponse UnitLogic::ClickLogic(const Unit& unit, Grid& grid, GridLogicHelper& logic_helper,
                                    std::pair<int, int> coord) const {
    if (coord == unit.get_coord()) {
        return {true, false, true};
    }
    if (!logic_helper.is_visited(coord)) {
        return {true, true, false};
    }
    unit.MoveTo(grid, coord);

    return {!unit.get_moves(), false, false};
}

void UnitLogic::Select(const SceneInfo &scene, GridLogicHelper &logic_helper, std::pair<int, int> coord,
                       const unsigned int max_moves) const {
    const Grid& grid = scene.grid;
    std::vector<std::pair<int, int>> visited_coords;

    std::deque<std::pair<int, int>> coords;

    visited_coords.push_back(coord);

    coords.push_back(coord);

    InitializeLogicHelper(logic_helper, coord);

    while (!coords.empty()) {
        std::pair<int, int> coord = coords.front();
        coords.pop_front();
        int moves_count = logic_helper.get_info(coord);
        if (moves_count + 1 > max_moves)
            continue;
        auto neighbours = grid.get_neighbours(coord);
        for (auto new_coord : neighbours) {
            if (grid.is_coord_out_of_range(new_coord) || logic_helper.is_visited(new_coord))
                continue;

            if (CellSkipCondition(*grid.get_cell(new_coord))) {
                continue;
            }
            logic_helper.visit(new_coord);
            visited_coords.push_back(new_coord);
            logic_helper.set_parent(new_coord, coord);


            BFSBodyHandler(logic_helper, max_moves, grid, coords, moves_count, new_coord);
        }
    }
    scene.selection_border.UpdateBorder(visited_coords);
}

void UnitLogic::BFSBodyHandler(GridLogicHelper &logic_helper, const unsigned int max_moves, const Grid &grid,
                    std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const {
    if (grid.get_cell(new_coord)->is_hittable())
        logic_helper.set_info(new_coord, static_cast<int>(max_moves));
    else {
        logic_helper.set_info(new_coord, moves_count + 1);
        coords.push_back(new_coord);
    }
}

void UnitLogic::InitializeLogicHelper(GridLogicHelper &logic_helper, std::pair<int, int> coord) const {
    logic_helper.increment_counter();
    logic_helper.visit(coord);
    logic_helper.set_info(coord, 0);
    logic_helper.set_parent(coord, coord);
}

bool UnitLogic::CellSkipCondition(const Cell &cell) const {
    return !cell.is_passable() && !cell.is_hittable();
}
