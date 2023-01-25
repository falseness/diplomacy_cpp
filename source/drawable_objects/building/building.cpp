#include "building.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/cell/coord_converter.h"

const BuildingStats& Building::get_stats() const {
    return cell_->get_player().get_stats().buildings.find(image_name_)->second;
}

Building::Building(Cell *cell, std::string image_name) : Entity(cell, std::move(image_name)) {
    if (!is_empty())
        get_player().AddBuilding(this);
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
    /* refactoring is required
    if (!is_empty()) {
        get_player().DeleteBuilding(this);
    }*/
}

bool EmptyBuilding::is_passable() const {
    return true;
}

EmptyBuilding::EmptyBuilding(Cell* cell) : Building(cell, std::string(Entity::kEmptyEntityName)),
    Entity(cell, std::string(Entity::kEmptyEntityName)) {}

void EmptyBuilding::Draw(Screen &, const GameOptions &) {}
