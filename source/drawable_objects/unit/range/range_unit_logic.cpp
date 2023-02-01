#include <deque>
#include "range_unit_logic.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects/unit/unit.h>
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>

const RangeUnitLogic RangeUnitLogic::kRangeUnitLogic = RangeUnitLogic();

bool RangeUnitLogic::CellSkipCondition(const Cell &cell, const Unit &unit) const {
    return !cell.can_be_shot_through() && !unit.is_attackable(cell);
}

void RangeUnitLogic::BFSBodyHandler(const unsigned int max_moves, const Unit &unit, const Grid &grid,
                                    std::deque<std::pair<int, int>> &coords, int moves_count,
                                    std::pair<int, int> new_coord) const {
    const Cell& cell = *grid.get_cell(new_coord);
    if (cell.can_be_shot_through()) {
        get_logic_helper(grid).set_info(new_coord, moves_count + 1);
        coords.push_back(new_coord);
    }
    else if (unit.is_attackable(cell)) {
        get_logic_helper(grid).set_info(new_coord, max_moves);
    }
}


void RangeUnitLogic::UpdateBorder(const SceneInfo &scene, vector<std::pair<int, int>> &visited_coords) const {
    scene.range_unit_attack_border.UpdateBorder(visited_coords, get_logic_helper(scene.grid));
}

GridLogicHelper &RangeUnitLogic::get_logic_helper(const Grid &grid) const {
    return grid.additional_logic_helper_;
}

ClickResponse RangeUnitLogic::MainClickLogic(const Unit &unit, Grid &grid, std::pair<int, int> &coord) const {
    if (!get_logic_helper(grid).is_visited(coord) || !unit.is_attackable(*grid.get_cell(coord))) {
        // we use another logic helper for melee logic
        return UnitLogic::kUnitLogic.MainClickLogic(unit, grid, coord);
    }

    auto range_unit = dynamic_cast<const RangeUnit&>(unit);
    range_unit.AttackSomething(grid, coord);

    return calculate_response_after_action(range_unit);
}
