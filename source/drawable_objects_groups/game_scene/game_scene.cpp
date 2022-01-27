#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>

GameScene::GameScene(Screen& screen, const GameOptions& game_options) : players_(
        {Player(Color(208, 208, 208)), Player(Color(255, 0, 0))}), grid_(players_), entity_interface_(screen) {
    drawable_objects_.push_back(&grid_);
    drawable_objects_.push_back(&entity_interface_);
}

void GameScene::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    grid_.HandleClick(click_pos, game_options);
}
