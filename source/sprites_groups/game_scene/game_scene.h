#include <source/sprites_groups/scene.h>
#include <source/sprites_groups/game_scene/grid.h>
#include <source/utility/all_usings.h>

#pragma once

class GameScene : public Scene {
    Grid grid_;
public:
    GameScene(const GameOptions&);
};
