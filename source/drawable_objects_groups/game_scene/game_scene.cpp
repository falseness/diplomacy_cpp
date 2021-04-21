#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>

GameScene::GameScene(const GameOptions& game_options) : grid_(game_options) {
    drawable_objects_.push_back(&grid_);
}
