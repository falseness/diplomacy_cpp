//
// Created by nikita on 29.01.2022.
//

#include "town.h"

const std::string Town::kTownImageName = "town";

Town::Town(const Cell* cell) : BuildingWithHp(cell, std::string(Town::kTownImageName)),
    SuburbBuilding(cell, std::string(Town::kTownImageName)), Building(cell, std::string(kTownImageName)) {
}
