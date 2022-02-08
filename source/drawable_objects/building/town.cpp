//
// Created by nikita on 29.01.2022.
//

#include "town.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/player/factories/building.h"

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

void Town::UpdateProductionInterface(SceneInfo &scene) {
    scene.town_production_interface.update(this);
}

std::vector<std::pair<int, int>> Town::get_suburbs() const {
    return suburbs_;
}

void Town::set_building_production_plan(std::string production_plan) {
    assert(!production_plan.empty());
    building_production_plan_ = std::move(production_plan);
}

void Town::Select(SceneInfo& scene) {
    if (building_production_plan_.empty()) {
        Barrack::Select(scene);
        return;
    }
    SelectionProductionInterface(scene);
    scene.entity_interface.set_visible(true);
}

ClickResponse Town::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions& game_options) {
    if (building_production_plan_.empty()) {
        return Barrack::HandleClick(scene, pos, game_options);
    }
    auto response = get_player().get_factories_stats().buildings_factory.
            find(building_production_plan_)->second->HandleClick(scene, pos, game_options, this);
    if (response.should_remove_selection) {
        building_production_plan_ = "";
        scene.selection_border.Clear();
        scene.entity_interface.set_visible(false);
        set_production_interface_visible(scene, false);
    }
    return response;
}

void Town::NextTurn() {
    building_production_plan_ = "";
    Barrack::NextTurn();
}

void Town::AddSuburb(std::pair<int, int> coord, Grid& grid) {
    auto cell = grid.get_cell(coord);
    assert(!cell->is_suburb());
    cell->set_suburb(true);
    suburbs_.push_back(coord);
}
