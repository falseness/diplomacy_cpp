#include <source/drawable_objects_groups/scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects_groups/interfaces/entity_info_interface.h>

#pragma once

class GameScene : public Scene {
    std::vector<Player> players_;
    Grid grid_;
    EntityInfoInterface entity_interface_;
public:
    GameScene(Screen& screen, const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
};
