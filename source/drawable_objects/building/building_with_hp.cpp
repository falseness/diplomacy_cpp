#include "building_with_hp.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/player/player.h>

BuildingWithHp::BuildingWithHp(Cell *cell, std::string&& image_name) :
    Building(cell, std::string(image_name)), Entity(cell, std::string(image_name)) {
    hp_ = get_stats().hp;
}

const BuildingWithHpStats& BuildingWithHp::get_stats() const {
    return cell_->get_player().get_stats().buildings_with_hp.find(image_name_)->second;
}

void BuildingWithHp::Kill() {
    cell_->DeleteBuilding();
}

unsigned int BuildingWithHp::get_maximum_hp() const {
    return get_stats().hp;
}
