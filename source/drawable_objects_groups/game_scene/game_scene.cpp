#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>

GameScene::GameScene(Screen& screen, const GameOptions&) : info_(screen) {
    drawable_objects_.push_back(&info_.grid);
    drawable_objects_.push_back(&info_.entity_interface);
}

void GameScene::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    info_.grid.HandleClick(info_, click_pos, game_options);
}

SceneInfo::SceneInfo(Screen& screen) : players({Player(Color(208, 208, 208)), Player(Color(255, 0, 0))}),
                                       grid(players), entity_interface(screen) {}
