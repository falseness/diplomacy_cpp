#include <source/drawable_objects/building/building.h>

#pragma once

class BuildingWithHpStats;

class BuildingWithHp : virtual public Building {
    unsigned int hp_;
public:
    [[nodiscard]] const BuildingWithHpStats& get_stats() const;
    BuildingWithHp(Cell* cell, std::string&& image_name);
    ~BuildingWithHp() override = default;
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] bool is_passable() const override;
};
