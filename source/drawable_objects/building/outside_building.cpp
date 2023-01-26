//
// Created by nikita on 26.01.23.
//

#include "outside_building.h"

OutsideBuilding::OutsideBuilding(Cell *cell, std::string image_name) : BuildingWithHp(cell, image_name),
                                                                       Building(cell, image_name),
                                                                       Entity(cell, std::move(image_name)) {}
