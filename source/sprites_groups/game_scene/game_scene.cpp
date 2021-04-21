#include <source/sprites_groups/game_scene/game_scene.h>
#include <source/sprites_groups/game_scene/grid.h>

GameScene::GameScene(const GameOptions& game_options) : grid_(game_options) {
    sprites_.push_back(&grid_);
}
