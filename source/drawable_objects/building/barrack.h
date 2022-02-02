#include <source/drawable_objects/building/suburb_building.h>
#include <source/player/entity_stats.h>

#pragma once

class Barrack : virtual public SuburbBuilding {
    ProductionInfo production_;
    bool production_in_progress_ = false;
public:
    [[nodiscard]] unsigned int get_turns_left() const;
    [[nodiscard]] bool is_production_in_progress() const;
    [[nodiscard]] std::string get_training_unit_name() const;
    void StartProduction(ProductionInfo);
    Barrack(Cell* cell, std::string&& image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void Select(SceneInfo&) override;
    void NextTurn() override;
    json get_info() const override;
};