#pragma once

#include <tuple>
#include <deque>

#include "source/drawable_objects/entity.h"

class Unit;
class Grid;
class SceneInfo;
class GridLogicHelper;

class UnitLogic {
    void InitializeLogicHelper(GridLogicHelper& logic_helper, std::pair<int, int> coord) const;
protected:
    [[nodiscard]] inline virtual GridLogicHelper& get_logic_helper(const Grid &grid) const;
    virtual bool CellSkipCondition(const Cell& cell) const;
    virtual void BFSBodyHandler(const unsigned int max_moves, const Unit &unit, const Grid &grid,
             std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const;
    virtual void UpdateBorder(const SceneInfo& scene, std::vector<std::pair<int, int>>& visited_coords) const;
public:
    virtual ClickResponse MainClickLogic(const Unit &unit, Grid &grid, std::pair<int, int> &coord) const;
    virtual void Select(const SceneInfo &scene, const Unit &unit, const unsigned int max_moves) const;
    // true if it should unselect unit

    virtual ClickResponse ClickLogic(const Unit& unit, Grid&, std::pair<int, int> coord) const;
    virtual ~UnitLogic() = default;
    static const UnitLogic kUnitLogic;

    ClickResponse calculate_response_after_action(const Unit &unit) const;
};