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

struct SceneInfo {
    Players players;
    Grid grid;
    SelectionBorder selection_border;
    EntityInfoInterface entity_interface;
    ProductionInterface production_interface;
    TownProductionInterface town_production_interface;
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
