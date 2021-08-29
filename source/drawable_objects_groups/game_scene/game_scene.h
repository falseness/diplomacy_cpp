#include <source/drawable_objects_groups/scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>

#pragma once

class GameScene : public Scene {
    std::vector<Player> players_;
    Grid grid_;
public:
    GameScene(const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
};
