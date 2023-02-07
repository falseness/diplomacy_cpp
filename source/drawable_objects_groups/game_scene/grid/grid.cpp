#include "grid.h"

#include <cassert>

#include <tuple>
#include <set>

#include "source/drawable_objects/cell/coord_converter.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/town.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/game_scene/grid/action.h"
#include "source/drawable_objects/building/nature.h"
#include "cells.h"




Grid::Grid(Players& players) : players_(players), logic_helper_(kGridRowsCount, kGridColumnsCount),
        additional_logic_helper_(kGridRowsCount, kGridColumnsCount), grid_cells_(kGridRowsCount, kGridColumnsCount, players_) {
    size_t n = kGridRowsCount;
    size_t m = kGridColumnsCount;
    auto& cells = grid_cells_.get_cells();

    for (auto& row : cells) {
        for (auto& cell : row) {
            drawable_objects_.push_back(cell.get());
        }
    }

    empty_unit_ = std::make_unique<EmptyUnit>(cells[0][0].get());
    selected_entity_= empty_unit_.get();
}

bool Grid::HandleClick(SceneInfo& scene, const Vector2D& screen_click_pos, const GameOptions& game_options) {
    Vector2D click_pos = screen_click_pos - game_options.draw_offset;
    if (selected_entity_->is_empty()) {
        std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
        if (is_coord_out_of_range(coord))
            return true;

        selected_entity_ = get_cell_ptr(coord)->get_unit_ptr();
        if (selected_entity_->is_empty()) {
            selected_entity_ = get_cell_ptr(coord)->get_building_ptr();
        }

        if (!selected_entity_->is_empty())
            selected_entity_->Select(scene);
        return true;
    }
    auto click_response = selected_entity_->HandleClick(scene, click_pos, game_options);

    if (click_response.should_change_selection_to_building_on_same_cell) {
        ChangeSelectedUnitToBuilding();
    }
    else if (click_response.should_remove_selection)
        RemoveSelection();

    if (!selected_entity_->is_empty())
        selected_entity_->Select(scene);

    if (click_response.should_reclick)
        HandleClick(scene, screen_click_pos, game_options);
    return true;
}


void Grid::ChangeSelectedUnitToBuilding() {
    assert(selected_entity_ != nullptr);
    auto coord = selected_entity_->get_coord();
    selected_entity_ = grid_cells_.get_cell_ptr(coord)->get_building_ptr();
}

const size_t Grid::kGridRowsCount = 15;
const size_t Grid::kGridColumnsCount = 6;

void Grid::RemoveSelection() {
    selected_entity_ = empty_unit_.get();
}

void Grid::MoveUnit(std::pair<int, int> from, std::pair<int, int> to) {
    MoveUnitAction action(from, to);
    PerformActionAndSaveUndo(action);
}

void Grid::StartProduction(std::pair<int, int> building_position, ProductionInfo production_info) {
    StartProductionAction action(building_position, std::move(production_info));
    PerformActionAndSaveUndo(action);
}

void Grid::DecreaseUnitMoves(std::pair<int, int> coord, int count) {
    DecreaseUnitMovesAction action(coord, count);
    PerformActionAndSaveUndo(action);
}

void Grid::AddSuburb(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord) {
    AddSuburbAction action(town_coord, new_suburb_coord);
    PerformActionAndSaveUndo(action);
}

void Grid::DecreaseUnitHP(std::pair<int, int> coord, int dmg) {
    DecreaseUnitHPAction action(coord, dmg);
    PerformActionAndSaveUndo(action);
}

void Grid::DecreaseBuildingHP(std::pair<int, int> coord, int dmg) {
    DecreaseBuildingHPAction action(coord, dmg);
    PerformActionAndSaveUndo(action);
}

void Grid::DeleteUnit(std::pair<int, int> coord) {
    DeleteUnitAction action(coord);
    PerformActionAndSaveUndo(action);
}

void Grid::DeleteBuilding(std::pair<int, int> coord) {
    DeleteBuildingAction action(coord);
    PerformActionAndSaveUndo(action);
}

void Grid::DeleteSuburb(std::pair<int, int> coord) {
    Town& town = get_cell_ptr(coord)->get_player().FindTown(coord);

    DeleteSuburbAction action(town.get_coord(), coord);

    PerformActionAndSaveUndo(action);
}

void Grid::SetPlayer(std::pair<int, int> coord, size_t player_index) {
    SetPlayerAction action(coord, player_index);
    PerformActionAndSaveUndo(action);
}

void Grid::IncreaseGold(size_t player_index, int gold_increase) {
    IncreasePlayersGold action(player_index, gold_increase);
    PerformActionAndSaveUndo(action);
}


void Grid::PerformAction(GridAction &action) {
    action.PerformAction(grid_cells_, players_);
}

void Grid::HandleKeyPress(SceneInfo& scene) {
    undo_button_.UndoAction(scene);
}

void Grid::ClearUndoStack() {
    undo_button_.Clear();
}

void Grid::PerformActionAndSaveUndo(GridAction &action) {
    undo_button_.AddAction(std::move(action.CreateUndoAction(grid_cells_)), selected_entity_, *this);
    PerformAction(action);
}

void Grid::StartUndoSequence() {
    undo_button_.StartActionSequence();
}

void Grid::SelectUnit(std::pair<int, int> coord, SceneInfo& scene) {
    auto unit = get_cell_ptr(coord)->get_unit_ptr();
    assert(!unit->is_empty());
    selected_entity_ = unit;
    unit->Select(scene);
}

void Grid::SelectBuilding(std::pair<int, int> coord, SceneInfo& scene) {
    auto building = get_cell_ptr(coord)->get_building_ptr();
    assert(!building->is_empty());
    selected_entity_ = building;
    building->Select(scene);
}

Vector2D Grid::get_right_bottom_corner(const GameOptions& game_options) const {
    return grid_cells_.get_cell(std::make_pair(grid_cells_.get_rows_count() - 1,
        grid_cells_.get_columns_count() - 1))->get_pos(game_options) + Vector2D(game_options.hexagon_options.radius * 2,
                                                                              game_options.hexagon_options.radius * 2);
}

void Grid::Draw(Screen &screen, const GameOptions & game_options) {
    DrawableObjectsGroup::Draw(screen, game_options);
    screen.DrawHexagonBuffer({0, 0});
    screen.DrawBuffer({0, 0});
}
