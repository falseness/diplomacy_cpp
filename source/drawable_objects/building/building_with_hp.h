#include <source/drawable_objects/building/building.h>

#pragma once

class BuildingWithHpStats;

class BuildingWithHp : virtual public Building {
    unsigned int hp_;
public:
    const BuildingWithHpStats& get_stats() const;
    BuildingWithHp(const Cell* cell, std::string&& image_name);
    ~BuildingWithHp() override = default;
    json get_info() const override;
};
