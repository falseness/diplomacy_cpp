#include "building.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/cell/coord_converter.h"

const BuildingStats& Building::get_stats() const {
    const auto& buildings_stats = cell_->get_player().get_stats().buildings;
    auto it = buildings_stats.find(image_name_);
    assert(it != buildings_stats.end());
    return it->second;
}

Building::Building(Cell *cell, std::string image_name) : Entity(cell, std::move(image_name)) {

}

ClickResponse Building::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) const {
    scene.selection_border.Clear();
    scene.entity_interface.set_visible(false);

    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    bool same_coord = get_coord() == coord;
    return {true, !same_coord, false};
}

void Building::NextTurn(SceneInfo& scene) {}

void Building::Select(const SceneInfo& scene) const {
    scene.selection_border.SelectCell(get_coord());
    Entity::Select(scene);
}

Building::~Building() {
    /* todo: refactoring
    if (!is_empty()) {
        get_player().DeleteBuilding(this);
    }*/
}

json Building::get_info() const {
    auto result = Entity::get_info();
    std::string additional_info;
    if (!can_be_shot_through()) {
        additional_info += "archers can't shoot..\n..through it\n";
    }
    if (is_high_ground()) {
        additional_info += "high ground\n";
    }
    auto additional_range = get_range_addition();
    if (additional_range) {
        additional_info += "archers get +" + std::to_string(additional_range) + " range\n";
    }
    // we think that if building is not passable for owner then it is not passable for everyone
    if (!is_passable(get_player_index())) {
        additional_info += "units can't stand on it\n";
    }
    if (!additional_info.empty()) {
        result["additional_info"] = additional_info;
    }
    return result;
}

void Building::Kill(Grid &grid) const {
    grid.DeleteBuilding(get_coord());
}

bool EmptyBuilding::is_passable(size_t) const {
    return true;
}

EmptyBuilding::EmptyBuilding(Cell* cell) : Building(cell, std::string(Entity::kEmptyEntityName)),
    Entity(cell, std::string(Entity::kEmptyEntityName)) {}

void EmptyBuilding::Draw(Screen &, const GameOptions &) {}
