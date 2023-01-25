#include "undo_button.h"

#include <cassert>

#include "source/drawable_objects/entity.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"



void UndoButton::AddAction(std::unique_ptr<GridAction>&& action, const Entity* entity, const Grid& grid) {
    assert(!undo_actions_stack_.empty());
    undo_actions_stack_.back().emplace_back(std::move(action), InitializeSelectedEntity(entity, grid));
}

optional<SelectedEntity> UndoButton::InitializeSelectedEntity(const Entity* entity, const Grid &grid) {
    if (entity->is_empty()) {
        return {};
    }
    auto coord = entity->get_coord();
    bool is_unit = grid.get_cell(coord)->get_unit() == entity;
    return SelectedEntity({coord, is_unit});
}

void UndoButton::UndoAction(Grid& grid) {
    if (undo_actions_stack_.empty()) {
        return;
    }
    if (undo_actions_stack_.back().empty()) {
        undo_actions_stack_.pop_back();
    }
    if (undo_actions_stack_.empty()) {
        return;
    }
    assert(!undo_actions_stack_.back().empty());
    reverse(undo_actions_stack_.back().begin(), undo_actions_stack_.back().end());
    for (auto& action : undo_actions_stack_.back()) {
        grid.PerformAction(*action.first);
    }
    undo_actions_stack_.pop_back();
}
