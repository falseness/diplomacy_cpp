#include <source/drawable_objects/entity.h>

#pragma once

class BuildingStats;

class Building : public virtual Entity {
    [[nodiscard]] const BuildingStats& get_stats() const;
public:
    Building(Cell* cell, std::string image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) const override;
    void NextTurn(SceneInfo& scene) override;
    void Select(const SceneInfo&) const override;
    [[nodiscard]] virtual inline bool can_be_shot_through() const {
        return true;
    }
    [[nodiscard]] virtual inline int get_range_addition() const {
        return 0;
    }
    [[nodiscard]] virtual inline bool can_be_shot() const {
        return !is_my_turn();
    }
    ~Building() override;
};

class EmptyBuilding : public Building {
public:
    [[nodiscard]] inline bool can_be_shot() const override {
        return false;
    }
    [[nodiscard]] bool is_passable() const override;
    explicit EmptyBuilding(Cell*);
    void Draw(Screen&, const GameOptions&) override;
};
