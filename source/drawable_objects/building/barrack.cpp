#include "barrack.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>

Barrack::Barrack(Cell *cell, std::string &&image_name) :
    SuburbBuilding(cell, std::string(image_name)), Building(cell, std::string(image_name)) {}

ClickResponse Barrack::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions& game_options) {
    auto result = Building::HandleClick(scene, pos, game_options);
    if (result.should_remove_selection)
        scene.production_interface.set_visible(false);
    return result;
}

void Barrack::Select(SceneInfo& scene) {
    scene.production_interface.set_visible(true);
    Entity::Select(scene);
}

