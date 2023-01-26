#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/cell/cell.h"

#pragma once


class RangeUnit : virtual public Unit {
protected:
    ClickResponse ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const override;
public:
    RangeUnit(Cell*, std::string);
    ClickResponse HandleClick(SceneInfo& scene, const Vector2D &click_pos,
                              const GameOptions &game_options) const override;
    [[nodiscard]] unsigned int get_range() const;
    void AttackSomething(Grid& grid, std::pair<int, int> cell_coord) const;
    [[nodiscard]] inline bool is_attackable(const Cell& cell) const override {
        return cell.is_hittable() || cell.get_building()->can_be_shot();
    }
    void Select(const SceneInfo&) const override;
};