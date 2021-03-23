#include <source/sprites_groups/game_scene/game_scene.h>
#include <source/sprites_groups/game_scene/grid.h>

GameScene::GameScene() {
    grid_ = new Grid();
    sprites_.push_back(grid_);
}

GameScene::~GameScene() {
    delete grid_;
}