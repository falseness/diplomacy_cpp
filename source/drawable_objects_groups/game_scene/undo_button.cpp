#include "undo_button.h"

#include <cassert>

#include "source/drawable_objects/entity.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"



void UndoButton::AddAction(GridAction& action, const Entity* entity, const Grid& grid) {
    /*assert(!(action.action_index & GridAction::kUndoMask));
    action.action_index ^= GridAction::kUndoMask;

    undo_actions_stack_.emplace_back(std::move(action), InitializeSelectedEntity(entity, grid));*/
}

optional<SelectedEntity> UndoButton::InitializeSelectedEntity(const Entity* entity, const Grid &grid) {
    /*if (entity->is_empty()) {
        return {};
    }
    auto coord = entity->get_coord();
    bool is_unit = grid.get_cell(coord)->get_unit() == entity;
    return SelectedEntity({coord, is_unit});*/
}
