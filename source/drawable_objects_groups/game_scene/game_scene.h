#include <source/drawable_objects_groups/scene.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects_groups/interfaces/entity_info.h>
#include <source/drawable_objects_groups/interfaces/production.h>
#include <source/player/players.h>
#include <source/next_turn/next_turn_button.h>

#pragma once

struct SceneInfo {
private:
    Players players;
public:
    Grid grid;
    EntityInfoInterface entity_interface;
    ProductionInterface production_interface;
    explicit SceneInfo(Screen& screen);
};

class GameScene : public Scene {
    SceneInfo info_;
    NextTurnButton next_turn_button_;
public:
    GameScene(Screen& screen, const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
};

