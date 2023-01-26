#include "source/drawable_objects/building/building_with_hp.h"

#pragma once

class OutsideBuilding : public BuildingWithHp {
public:
    OutsideBuilding(Cell* cell, std::string image_name);
    [[nodiscard]] inline bool can_be_shot_through() const override {
        return false;
    }
};
