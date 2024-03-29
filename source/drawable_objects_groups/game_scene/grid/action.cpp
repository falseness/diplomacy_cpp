#include "action.h"

#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/building/town.h"
#include "source/player/players.h"


void StartProductionAction::PerformAction(GridCells &cells, Players &players) {
    auto barrack = dynamic_cast<Barrack*>(cells.get_cell_ptr(building_position_)->get_building_ptr());
    assert(barrack);
    barrack->StartProduction(std::move(production_info_));
}

std::unique_ptr<GridAction> StartProductionAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<UndoStartedProductionAction>(building_position_);
}

void MoveUnitAction::PerformAction(GridCells &cells, Players &players) {
    cells.get_cell_ptr(from_)->MoveUnitTo(*cells.get_cell_ptr(to_));
}

std::unique_ptr<GridAction> MoveUnitAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<MoveUnitAction>(to_, from_);
}

void DecreaseUnitMovesAction::PerformAction(GridCells &cells, Players &players) {
    auto unit = cells.get_cell_ptr(coord_)->get_unit_ptr();
    assert(!unit->is_empty());
    unit->DecreaseMoves(count_);
}

std::unique_ptr<GridAction> DecreaseUnitMovesAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<DecreaseUnitMovesAction>(coord_, -count_);
}

void AddSuburbAction::PerformAction(GridCells &cells, Players &players) {
    auto town = dynamic_cast<Town*>(cells.get_cell_ptr(town_coord_)->get_building_ptr());
    assert(town);
    town->AddSuburb(cells.get_cell_ptr(new_suburb_coord_).get());
}

std::unique_ptr<GridAction> AddSuburbAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<DeleteSuburbAction>(town_coord_, new_suburb_coord_);
}

void DecreaseUnitHPAction::PerformAction(GridCells &cells, Players &players) {
    cells.get_cell_ptr(coord_)->get_unit_ptr()->DecreaseHP(dmg_);
}

std::unique_ptr<GridAction> DecreaseUnitHPAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<DecreaseUnitHPAction>(coord_, -dmg_);
}

void DecreaseBuildingHPAction::PerformAction(GridCells &cells, Players &players) {
    dynamic_cast<HittableEntity*>(cells.get_cell_ptr(coord_)->get_building_ptr())->DecreaseHP(dmg_);
}

std::unique_ptr<GridAction> DecreaseBuildingHPAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<DecreaseBuildingHPAction>(coord_, -dmg_);
}

void DeleteUnitAction::PerformAction(GridCells &cells, Players &players) {
    cells.get_cell_ptr(coord_)->DeleteUnit();
}

std::unique_ptr<GridAction> DeleteUnitAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<RestoreLastUnitAction>(coord_);
}

void DeleteBuildingAction::PerformAction(GridCells &cells, Players &players) {
    cells.get_cell_ptr(coord_)->DeleteBuilding();
}

std::unique_ptr<GridAction> DeleteBuildingAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<RestoreLastBuildingAction>(coord_);
}

void DeleteSuburbAction::PerformAction(GridCells &cells, Players &players) {
    auto town = dynamic_cast<Town*>(cells.get_cell_ptr(town_coord_)->get_building_ptr());
    assert(town);
    town->DeleteSuburb(cells.get_cell_ptr(suburb_coord_).get());
}

std::unique_ptr<GridAction> DeleteSuburbAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<AddSuburbAction>(town_coord_, suburb_coord_);
}

void SetPlayerAction::PerformAction(GridCells &cells, Players &players) {
    cells.get_cell_ptr(coord_)->set_player(player_index_);
}

std::unique_ptr<GridAction> SetPlayerAction::CreateUndoAction(GridCells &cells) {
    return std::make_unique<SetPlayerAction>(coord_, cells.get_cell_ptr(coord_)->get_player_index());
}

void RestoreLastUnitAction::PerformAction(GridCells &cells, Players &players) {
    auto& cell = *cells.get_cell_ptr(coord_);
    cell.SetUnit(cell.get_player().get_last_deleted_unit());
}

std::unique_ptr<GridAction> RestoreLastUnitAction::CreateUndoAction(GridCells &cells) {
    assert(false);
    return {};
}

void RestoreLastBuildingAction::PerformAction(GridCells &cells, Players &players) {
    auto& cell = *cells.get_cell_ptr(coord_);
    cell.SetBuilding(cell.get_player().get_last_deleted_building());
}

std::unique_ptr<GridAction> RestoreLastBuildingAction::CreateUndoAction(GridCells &cells) {
    assert(false);
    return {};
}

void UndoStartedProductionAction::PerformAction(GridCells &cells, Players &players) {
    auto barrack = dynamic_cast<Barrack*>(cells.get_cell_ptr(building_position_)->get_building_ptr());
    assert(barrack);
    barrack->UndoStartedProduction();
}

std::unique_ptr<GridAction> UndoStartedProductionAction::CreateUndoAction(GridCells &cells) {
    assert(false);
    return {};
}

void IncreasePlayersGold::PerformAction(GridCells &cells, Players &players) {
    players[player_index_].IncreaseGold(gold_increase_);
}

std::unique_ptr<GridAction> IncreasePlayersGold::CreateUndoAction(GridCells &cells) {
    return std::make_unique<IncreasePlayersGold>(player_index_, -gold_increase_);
}
