#include <source/drawable_objects_groups/scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects_groups/interfaces/entity_info_interface.h>

#pragma once

struct SceneInfo {
private:
    std::vector<Player> players;
public:
    Grid grid;
    EntityInfoInterface entity_interface;
    explicit SceneInfo(Screen& screen);
};

class GameScene : public Scene {
    SceneInfo info_;
public:
    GameScene(Screen& screen, const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
};

