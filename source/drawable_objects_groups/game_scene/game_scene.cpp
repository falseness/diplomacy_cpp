#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>


GameScene::GameScene(Screen& screen, const GameOptions&) : info_(screen), next_turn_button_(screen) {
    drawable_objects_.push_back(&info_.grid);
    drawable_objects_.push_back(&next_turn_button_);
    drawable_objects_.push_back(&info_.entity_interface);
    drawable_objects_.push_back(&info_.production_interface);

    clickable_objects_.push_back(&info_.grid);
    clickable_objects_.push_back(&next_turn_button_);
}

void GameScene::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    for (auto it = clickable_objects_.rbegin(); it != clickable_objects_.rend(); ++it) {
        if ((*it)->HandleClick(info_, click_pos, game_options))
            break;
    }
}

SceneInfo::SceneInfo(Screen& screen) : players({Player(Color(208, 208, 208)), Player(Color(255, 0, 0))}, 1),
                                       grid(players), entity_interface(screen), production_interface(screen) {}
