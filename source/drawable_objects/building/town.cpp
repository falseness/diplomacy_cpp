//
// Created by nikita on 29.01.2022.
//

#include "town.h"

const std::string Town::kTownImageName = "town";

Town::Town(const Cell* cell) : BuildingWithHp(cell, std::string(Town::kTownImageName)),
    SuburbBuilding(cell, std::string(Town::kTownImageName)), Building(cell, std::string(kTownImageName)) {
}

json Town::get_info() const {
    auto result = SuburbBuilding::get_info();
    result["info"]["hp"] = BuildingWithHp::get_info()["info"]["hp"];
    return result;
}
