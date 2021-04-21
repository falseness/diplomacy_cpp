#include <source/drawable_objects_groups/scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/utility/all_usings.h>

#pragma once

class GameScene : public Scene {
    std::vector<Player> players_;
    Grid grid_;
public:
    GameScene(const GameOptions&);
};
