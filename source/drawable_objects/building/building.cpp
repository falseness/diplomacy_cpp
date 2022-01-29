#include "building.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects/cell/coord_converter.h>

const BuildingStats& Building::get_stats() const {
    return cell_->get_player().get_stats().buildings.find(image_name_)->second;
}

Building::Building(const Cell *cell, std::string &&image_name) : Entity(cell, std::move(image_name)) {}

ClickResponse Building::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) {
    scene.entity_interface.set_visible(false);

    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    bool same_coord = get_coord() == coord;
    return {true, !same_coord, false};
}
