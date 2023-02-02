//
// Created by nikita on 29.01.2022.
//

#include "town.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/player/factories/building_and_suburb.h"


Town::Town(Cell* cell, std::string&& image_name, std::set<std::pair<int, int>> suburbs) :
        BuildingWithHp(cell, std::string(image_name)), Barrack(cell, std::string(image_name)),
        SuburbBuilding(cell, std::string(image_name)), Building(cell, std::string(image_name)),
        Entity(cell, std::string(image_name)), suburbs_(std::move(suburbs)) {
}

json Town::get_info() const {
    auto result = Barrack::get_info();
    result["info"]["hp"] = BuildingWithHp::get_info()["info"]["hp"].get<std::string>();
    return result;
}

bool Town::is_passable(size_t asking_player_index) const {
    return BuildingWithHp::is_passable(asking_player_index);
}

bool Town::is_hittable(size_t asking_player_index) const {
    return BuildingWithHp::is_hittable(asking_player_index);
}

void Town::set_production_interface_visible(const SceneInfo& scene, bool visibility) const {
    scene.town_production_interface.set_visible(visibility);
}

void Town::UpdateProductionInterface(const SceneInfo &scene) const {
    scene.town_production_interface.update(this);
}

void Town::set_building_production_plan(std::string production_plan) const {
    assert(!production_plan.empty());
    building_production_plan_ = std::move(production_plan);
}

void Town::Select(const SceneInfo& scene) const {
    if (building_production_plan_.empty()) {
        Barrack::Select(scene);
        return;
    }
    SelectionProductionInterface(scene);
    scene.entity_interface.set_visible(true);
}

ClickResponse Town::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions& game_options) const {
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

void Town::NextTurn(SceneInfo& scene) {
    clear_building_production_plan();
    Barrack::NextTurn(scene);
}

void Town::AddSuburb(Cell* cell) {
    assert(cell && !cell->is_suburb());
    cell->set_suburb(true);
    bool was_inserted = suburbs_.insert(cell->get_coord()).second;
    assert(was_inserted);
}

void Town::Kill(Grid &grid) const {
    // suburbs_ may be changed in these loops
    auto suburbs_copy = suburbs_;
    for (auto suburb : suburbs_copy) {
        if (suburb == get_coord()) {
            continue;
        }
        if (grid.get_cell(suburb)->get_building()->should_be_destroyed_after_town_destroying()) {
            grid.DeleteBuilding(suburb);
        }
    }
    for (auto suburb : suburbs_copy) {
        grid.DeleteSuburb(suburb);
    }

    BuildingWithHp::Kill(grid);
}

void Town::DeleteSuburb(Cell *cell) {
    assert(cell && cell->is_suburb());
    cell->set_suburb(false);
    bool was_erased = suburbs_.erase(cell->get_coord());
    assert(was_erased);
}
