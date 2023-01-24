#include "source/drawable_objects_groups/scene.h"
#include "source/drawable_objects_groups/game_scene/grid.h"
#include "source/drawable_objects_groups/interfaces/entity_info.h"
#include "source/drawable_objects_groups/interfaces/unit_production.h"
#include "source/drawable_objects_groups/interfaces/town_production.h"
#include "source/player/players.h"
#include "source/next_turn/next_turn_button.h"
#include "source/drawable_objects/clickable_object.h"
#include "source/drawable_objects/selection_border.h"

#pragma once

// fields are mutable if they are not related to game information but to interfaces and etc.
struct SceneInfo {
    Players players;
    Grid grid;
    mutable SelectionBorder selection_border;
    mutable EntityInfoInterface entity_interface;
    mutable ProductionInterface production_interface;
    mutable TownProductionInterface town_production_interface;
    explicit SceneInfo(Screen& screen);
};

class GameScene : public Scene {
    SceneInfo info_;
    NextTurnButton next_turn_button_;
    std::vector<ClickableObject*> clickable_objects_;
public:
    GameScene(Screen& screen, const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
};
