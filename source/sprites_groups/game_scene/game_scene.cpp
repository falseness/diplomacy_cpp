#include <source/sprites_groups/game_scene/game_scene.h>
#include <source/sprites_groups/game_scene/grid.h>

GameScene::GameScene(const GameOptions& game_options) {
    grid_ = new Grid(game_options);
    sprites_.push_back(grid_);
}

GameScene::~GameScene() {
    delete grid_;
}