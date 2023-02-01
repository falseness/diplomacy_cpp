#include "source/drawable_objects/building/building.h"

#pragma once

class SuburbBuildingStats;

class SuburbBuilding : virtual public Building {
public:
    [[nodiscard]] const SuburbBuildingStats& get_stats() const;
    SuburbBuilding(Cell* cell, std::string image_name);
    ~SuburbBuilding() override = default;
    [[nodiscard]] virtual int get_income() const;
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] inline bool is_passable(size_t asking_player_index) const override {
        return true;
    }
    [[nodiscard]] bool is_hittable(size_t asking_player_index) const override;
    [[nodiscard]] inline bool should_be_destroyed_after_town_destroying() const override {
        return true;
    }
    void NextTurn(SceneInfo& scene) override;
};
