#include "outside_building.h"

OutsideBuilding::OutsideBuilding(Cell *cell, std::string image_name) : BuildingWithHp(cell, image_name),
                                                                       Building(cell, image_name),
                                                                       Entity(cell, std::move(image_name)) {}

Wall::Wall(Cell *cell, std::string image_name) : OutsideBuilding(cell, image_name),
                                                 Building(cell, image_name),
                                                 Entity(cell, std::move(image_name)) {

}

Tower::Tower(Cell *cell, std::string image_name) : OutsideBuilding(cell, image_name),
                                                   Building(cell, image_name),
                                                   Entity(cell, std::move(image_name)) {

}
