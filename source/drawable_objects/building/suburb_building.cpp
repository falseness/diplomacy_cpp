#include "suburb_building.h"
#include <source/player/player.h>
#include <source/drawable_objects/cell/cell.h>


const SuburbBuildingStats& SuburbBuilding::get_stats() const {
    return cell_->get_player().get_stats().suburb_buildings.find(image_name_)->second;
}

SuburbBuilding::SuburbBuilding(Cell *cell, std::string image_name) : Building(cell, image_name),
    Entity(cell, std::move(image_name)) {
}

json SuburbBuilding::get_info() const {
    auto result = Building::get_info();
    result["info"]["income"] = get_income();
    return result;
}

int SuburbBuilding::get_income() const {
    return get_stats().income;
}

bool SuburbBuilding::is_hittable(size_t asking_player_index) const {
    return false;
}

void SuburbBuilding::NextTurn(SceneInfo &scene) {
    Building::NextTurn(scene);
}
