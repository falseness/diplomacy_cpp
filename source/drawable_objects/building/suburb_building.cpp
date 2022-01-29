#include "suburb_building.h"
#include <source/drawable_objects/cell/cell.h>

const SuburbBuildingStats& SuburbBuilding::get_stats() const {
    return cell_->get_player().get_stats().suburb_buildings.find(image_name_)->second;
}

SuburbBuilding::SuburbBuilding(const Cell *cell, std::string &&image_name) : Building(cell, std::move(image_name)) {

}
