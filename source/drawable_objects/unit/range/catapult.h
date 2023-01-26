#pragma once

#include "source/drawable_objects/unit/range/range_unit.h"


class Catapult : public RangeUnit {
    void AttackAfterPreparations(Grid &grid, std::pair<int, int> &cell_coord, const Cell &cell) const override;
    void CallUnitLogicSelect(const SceneInfo &scene, unsigned int bfs_moves) const override;
    ClickResponse ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const override;
public:
    [[nodiscard]] inline bool is_attackable(const Cell& cell) const override {
        return cell.get_building()->can_be_shot();
    }
    Catapult(Cell*, std::string);
};
