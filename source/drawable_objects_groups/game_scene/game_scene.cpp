#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include "source/drawable_objects_groups/game_scene/grid/grid.h"


GameScene::GameScene(Screen& screen, const GameOptions& game_options) : info_(screen), next_turn_button_(screen) {
    drawable_objects_.push_back(&info_.grid);
    drawable_objects_.push_back(&info_.selection_border);
    drawable_objects_.push_back(&next_turn_button_);
    drawable_objects_.push_back(&info_.entity_interface);
    drawable_objects_.push_back(&info_.production_interface);
    drawable_objects_.push_back(&info_.town_production_interface);

    clickable_objects_.push_back(&info_.grid);
    clickable_objects_.push_back(&next_turn_button_);
    clickable_objects_.push_back(&info_.entity_interface);
    clickable_objects_.push_back(&info_.production_interface);
    clickable_objects_.push_back(&info_.town_production_interface);
}

void GameScene::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    info_.grid.StartUndoSequence();
    for (auto it = clickable_objects_.rbegin(); it != clickable_objects_.rend(); ++it) {
        if ((*it)->HandleClick(info_, click_pos, game_options))
            break;
    }
}

void GameScene::HandleKeyBackspacePress() {
    info_.grid.HandleKeyPress(info_);
}

void GameScene::HandleKeyEnterPress() {
    next_turn_button_.NextTurn(info_);
}

SceneInfo::SceneInfo(Screen& screen) :
        players({Color(80, 80, 80), Color(255, 0, 0), Color(0, 255, 0)}, 1), grid(players), selection_border(grid),
        entity_interface(screen), production_interface(screen), town_production_interface(screen) {}

void SceneInfo::ClearInterfaces() {
    selection_border.Clear();
    entity_interface.set_visible(false);
    town_production_interface.set_visible(false);
    production_interface.set_visible(false);
}
