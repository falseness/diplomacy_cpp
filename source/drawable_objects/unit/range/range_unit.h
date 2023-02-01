#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/cell/cell.h"

#pragma once


class RangeUnit : virtual public Unit {
protected:
    ClickResponse ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const override;
    virtual void AttackAfterPreparations(Grid &grid, std::pair<int, int> &cell_coord, const Cell &cell) const;
    virtual void CallUnitLogicSelect(const SceneInfo &scene, unsigned int bfs_moves) const;
    [[nodiscard]] unsigned int get_unit_base_range() const;
public:
    [[nodiscard]] inline bool can_melee_interact(const Cell& cell) const override {
        return cell.is_passable(get_player_index()) && !is_attackable(cell);
    }
    RangeUnit(Cell*, std::string);
    ClickResponse HandleClick(SceneInfo& scene, const Vector2D &click_pos,
                              const GameOptions &game_options) const override;
    [[nodiscard]] virtual unsigned int get_range() const;
    void AttackSomething(Grid& grid, std::pair<int, int> cell_coord) const;
    [[nodiscard]] inline bool is_attackable(const Cell& cell) const override {
        return cell.is_hittable(get_player_index()) || cell.get_building()->can_be_shot(get_player_index());
    }
    void Select(const SceneInfo&) const override;
};