#include "undo_button.h"

#include <cassert>

#include "source/drawable_objects/entity.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"



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

void UndoButton::UndoAction(SceneInfo& scene) {
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
        scene.grid.PerformAction(*action.first);
    }
    auto& selected_entity = undo_actions_stack_.back().back().second;
    scene.grid.RemoveSelection();
    scene.ClearInterfaces();
    undo_actions_stack_.pop_back();
    if (!selected_entity) {
        return;
    }
    if (selected_entity.value().is_unit) {
        scene.production_interface.set_visible(false);
        scene.town_production_interface.set_visible(false);
        scene.grid.SelectUnit(selected_entity.value().coord, scene);
    }
    else {
        scene.grid.SelectBuilding(selected_entity.value().coord, scene);
    }
}
