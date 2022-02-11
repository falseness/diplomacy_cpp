#include "source/drawable_objects/building/building.h"

#pragma once

class SuburbBuildingStats;

class SuburbBuilding : virtual public Building {
public:
    [[nodiscard]] const SuburbBuildingStats& get_stats() const;
    SuburbBuilding(Cell* cell, std::string image_name);
    ~SuburbBuilding() override = default;
    [[nodiscard]] int get_income() const;
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
};
