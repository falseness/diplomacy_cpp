#include <source/drawable_objects/entity.h>

#pragma once

class BuildingStats;

class Building : public Entity {
    [[nodiscard]] const BuildingStats& get_stats() const;
public:
    Building(Cell* cell, std::string&& image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    void NextTurn() override;
    ~Building() override = default;
};
