#pragma once

#include <vector>
#include <tuple>

#include "source/drawable_objects_groups/game_scene/grid/action.h"


using std::vector;
class Entity;
class Scen;
class SceneInfo;

class UndoButton {
    vector<vector<std::pair<std::unique_ptr<GridAction>, optional<SelectedEntity>>>> undo_actions_stack_;
    static optional<SelectedEntity> InitializeSelectedEntity(const Entity* entity, const Grid& grid);
public:
    void AddAction(std::unique_ptr<GridAction>&& action, const Entity* entity, const Grid& grid);
    inline void Clear() {
        undo_actions_stack_.clear();
    }
    inline void StartActionSequence() {
        if (undo_actions_stack_.empty() || !undo_actions_stack_.back().empty()) {
            undo_actions_stack_.emplace_back();
        }
    }
    void UndoAction(SceneInfo& scene);
};