#include <source/drawable_objects/entity.h>

#pragma once

class BuildingStats;

class Building : public virtual Entity {
    [[nodiscard]] const BuildingStats& get_stats() const;
public:
    Building(Cell* cell, std::string image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) const override;
    void NextTurn() override;
    void Select(const SceneInfo&) const override;
    ~Building() override;
};

class EmptyBuilding : public Building {
public:
    [[nodiscard]] bool is_passable() const override;
    explicit EmptyBuilding(Cell*);
    void Draw(Screen&, const GameOptions&) override;
};
