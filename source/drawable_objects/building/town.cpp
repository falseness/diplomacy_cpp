//
// Created by nikita on 29.01.2022.
//

#include "town.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>

Town::Town(Cell* cell, std::string&& image_name, std::vector<std::pair<int, int>>&& suburbs) :
    BuildingWithHp(cell, std::string(image_name)), Barrack(cell, std::string(image_name)),
    SuburbBuilding(cell, std::string(image_name)), Building(cell, std::string(image_name)),
    Entity(cell, std::string(image_name)), suburbs_(std::move(suburbs)) {}

json Town::get_info() const {
    auto result = Barrack::get_info();
    result["info"]["hp"] = BuildingWithHp::get_info()["info"]["hp"];
    return result;
}

bool Town::is_passable() const {
    return BuildingWithHp::is_passable();
}

bool Town::is_hittable() const {
    return BuildingWithHp::is_hittable();
}

void Town::set_production_interface_visible(SceneInfo& scene, bool visibility) const {
    scene.town_production_interface.set_visible(visibility);
}

void Town::update_production_interface(SceneInfo &scene) {
    scene.town_production_interface.update(this);
}
