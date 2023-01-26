#include <deque>
#include "unit_logic.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects/unit/unit.h>
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid_logic_helper.h"

const UnitLogic UnitLogic::kUnitLogic = UnitLogic();


ClickResponse UnitLogic::ClickLogic(const Unit& unit, Grid& grid, std::pair<int, int> coord) const {
    if (coord == unit.get_coord()) {
        return {true, false, true};
    }

    return MainClickLogic(unit, grid, coord);

}

ClickResponse UnitLogic::MainClickLogic(const Unit &unit, Grid &grid, std::pair<int, int> &coord) const {
    if (!get_logic_helper(grid).is_visited(coord)) {
        return {true, true, false};
    }
    unit.MoveTo(grid, coord);

    return calculate_response_after_action(unit);
}

ClickResponse UnitLogic::calculate_response_after_action(const Unit &unit) const {
    return {!unit.get_moves(), false, false};
}

void UnitLogic::Select(const SceneInfo &scene, const Unit &unit, const unsigned int max_moves) const {
    auto unit_coord = unit.get_coord();
    const Grid& grid = scene.grid;
    GridLogicHelper& logic_helper = get_logic_helper(grid);
    std::vector<std::pair<int, int>> visited_coords;

    std::deque<std::pair<int, int>> coords;

    visited_coords.push_back(unit_coord);

    coords.push_back(unit_coord);

    InitializeLogicHelper(logic_helper, unit_coord);

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


            BFSBodyHandler(max_moves, unit, grid, coords, moves_count, new_coord);
        }
    }
    UpdateBorder(scene, visited_coords);
}

void UnitLogic::BFSBodyHandler(const unsigned int max_moves, const Unit &, const Grid &grid,
                    std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const {
    if (grid.get_cell(new_coord)->is_hittable())
        get_logic_helper(grid).set_info(new_coord, static_cast<int>(max_moves));
    else {
        get_logic_helper(grid).set_info(new_coord, moves_count + 1);
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

void UnitLogic::UpdateBorder(const SceneInfo &scene, vector<std::pair<int, int>> &visited_coords) const {
    scene.selection_border.UpdateBorder(visited_coords, get_logic_helper(scene.grid));
}

GridLogicHelper &UnitLogic::get_logic_helper(const Grid &grid) const {
    return grid.logic_helper_;
}

