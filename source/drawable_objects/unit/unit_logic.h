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
    virtual bool CellSkipCondition(const Cell& cell) const;
    virtual void BFSBodyHandler(GridLogicHelper &logic_helper, const unsigned int max_moves, const Grid &grid,
             std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const;
public:
    virtual void Select(const SceneInfo &scene, GridLogicHelper &logic_helper, std::pair<int, int> coord,
                        const unsigned int max_moves) const;
    // true if it should unselect unit

    virtual ClickResponse ClickLogic(const Unit& unit, Grid&, GridLogicHelper& logic_helper,
                                     std::pair<int, int> coord) const;
    virtual ~UnitLogic() = default;
    static const UnitLogic kUnitLogic;
};