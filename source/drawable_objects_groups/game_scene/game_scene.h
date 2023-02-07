#include "source/drawable_objects_groups/scene.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/interfaces/entity_info.h"
#include "source/drawable_objects_groups/interfaces/unit_production.h"
#include "source/drawable_objects_groups/interfaces/town_production.h"
#include "source/player/players.h"
#include "source/next_turn/next_turn_button.h"
#include "source/next_turn/sudden_death_info.h"
#include "source/drawable_objects/clickable_object.h"
#include "source/drawable_objects/selection_border.h"
#include "source/utility/arrow_key_press_info.h"

#pragma once

// fields are mutable if they are not related to game information but to interfaces etc.
struct SceneInfo {
    Players players;
    Grid grid;
    GridRegularCellInfo cells_text;
    mutable SelectionBorder selection_border;
    mutable TwoLayersSelectionBorder range_unit_attack_border;
    mutable EntityInfoInterface entity_interface;
    mutable ProductionInterface production_interface;
    mutable TownProductionInterface town_production_interface;
    SuddenDeathInfo sudden_death_info;
    explicit SceneInfo(Screen& screen);
    void ClearInterfaces();
};

class GameScene : public Scene {
    SceneInfo info_;
    NextTurnButton next_turn_button_;
    std::vector<ClickableObject*> clickable_objects_;
public:
    GameScene(Screen& screen, const GameOptions&);
    void HandleClick(const Vector2D&, const GameOptions&) override;
    void HandleKeyBackspacePress();
    void HandleKeyEnterPress();
    void HandleArrowKeyPress(ArrowsKeyPressInfo arrows_info, Screen& screen, const GameOptions& game_options);
};
