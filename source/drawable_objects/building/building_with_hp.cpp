#include "building_with_hp.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/player/player.h>

BuildingWithHp::BuildingWithHp(const Cell *cell, std::string&& image_name) : Building(cell, std::move(image_name)) {
    hp_ = get_stats().hp;
}

const BuildingWithHpStats &BuildingWithHp::get_stats() const {
    return cell_->get_player().get_stats().buildings_with_hp.find(image_name_)->second;
}

json BuildingWithHp::get_info() const {
    auto result = Entity::get_info();
    result["info"]["hp"] = hp_;
    return result;
}
