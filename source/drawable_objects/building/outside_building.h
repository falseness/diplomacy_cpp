#include "source/drawable_objects/building/building_with_hp.h"

#pragma once

class OutsideBuilding : public BuildingWithHp {
public:
    OutsideBuilding(Cell* cell, std::string image_name);
    [[nodiscard]] inline bool can_be_shot_through() const override {
        return false;
    }
};

class Wall : public OutsideBuilding {
public:
    Wall(Cell* cell, std::string image_name);
    [[nodiscard]] inline bool is_passable() const override {
        return false;
    }
};

class Tower : public OutsideBuilding {
    static const int kTowerRangeAddition = 1;
public:
    Tower(Cell* cell, std::string image_name);
    [[nodiscard]] inline int get_range_addition() const override {
        return kTowerRangeAddition;
    }
};
