#include <tuple>
#include "source/drawable_objects/entity.h"
#include "source/drawable_objects/unit/unit_logic.h"
#include "source/drawable_objects/unit/range/archer.h"

#pragma once

class Unit;
class Grid;
class SceneInfo;

class RangeUnitLogic : public UnitLogic {
protected:
    [[nodiscard]] inline GridLogicHelper& get_logic_helper(const Grid &grid) const override;
    [[nodiscard]] bool CellSkipCondition(const Cell& cell) const override;
    void BFSBodyHandler(const unsigned int max_moves, const Unit &unit, const Grid &grid,
            std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const override;
    void UpdateBorder(const SceneInfo& scene, std::vector<std::pair<int, int>>& visited_coords) const override;
    ClickResponse MainClickLogic(const Unit &unit, Grid &grid, std::pair<int, int> &coord) const override;
public:
    static const RangeUnitLogic kRangeUnitLogic;
};
