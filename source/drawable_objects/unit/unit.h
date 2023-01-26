#pragma once

#include "source/drawable_objects/hittable_entity.h"
#include "source/player/entity_stats.h"
#include "source/drawable_objects/unit/unit_logic.h"

class Grid;
class SceneInfo;

// Todo : refactor using multiple inheritance with UnitLogic
class Unit : virtual public HittableEntity {
protected:
    int dmg_;
    unsigned int moves_;
    void Kill(Grid& grid) const override;
    void AskGridToDecreaseHP(int dmg, Grid& grid) const override;
    virtual ClickResponse ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const;
public:
    void NextTurn(SceneInfo& scene) override;
    [[nodiscard]] const UnitStats& get_stats() const;
    [[nodiscard]] unsigned int get_speed() const;
    [[nodiscard]] unsigned int get_maximum_hp() const override;
    void Select(const SceneInfo&) const override;
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) const override;
    Unit(Cell*, std::string);
    void set_cell(Cell*);
    [[nodiscard]] unsigned int get_moves() const;
    void MoveTo(Grid& grid, std::pair<int, int> coord) const;
    // count may be negative. it is ok.
    inline void DecreaseMoves(int count) {
        assert(static_cast<int>(moves_) >= count);
        moves_ -= count;
    }
    [[nodiscard]] json to_json() override;
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] inline virtual bool is_attackable(const Cell& cell) const;
    ~Unit() override = default;
};

class EmptyUnit : public Unit {
protected:
    inline void AskGridToDecreaseHP(int, Grid&) const override {
        assert(false);
    }
public:
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
    explicit EmptyUnit(Cell*);
    void Draw(Screen&, const GameOptions&) override;
    void Select(const SceneInfo&) const override;
};
