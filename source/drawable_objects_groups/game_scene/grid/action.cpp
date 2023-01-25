#include "action.h"

#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/building/town.h"


void StartProductionAction::PerformAction(GridCells &cells) {
    auto barrack = dynamic_cast<Barrack*>(cells.get_cell_ptr(building_position_)->get_building_ptr());
    assert(barrack);
    barrack->StartProduction(std::move(production_info_));
}

void MoveUnitAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(from_)->MoveUnitTo(*cells.get_cell_ptr(to_));
}

void DecreaseUnitMovesAction::PerformAction(GridCells &cells) {
    auto unit = cells.get_cell_ptr(coord_)->get_unit_ptr();
    assert(!unit->is_empty());
    unit->DecreaseMoves(count_);
}

void AddSuburbAction::PerformAction(GridCells &cells) {
    auto town = dynamic_cast<Town*>(cells.get_cell_ptr(town_coord_)->get_building_ptr());
    assert(town);
    town->AddSuburb(cells.get_cell_ptr(new_suburb_coord_).get());
}

void DecreaseUnitHPAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(coord_)->get_unit_ptr()->DecreaseHP(dmg_);
}

void DecreaseBuildingHPAction::PerformAction(GridCells &cells) {
    dynamic_cast<HittableEntity*>(cells.get_cell_ptr(coord_)->get_building_ptr())->DecreaseHP(dmg_);
}

void DeleteUnitAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(coord_)->DeleteUnit();
}

void DeleteBuildingAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(coord_)->DeleteBuilding();
}

void DeleteSuburbAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(coord_)->set_suburb(false);
}

void SetPlayerAction::PerformAction(GridCells &cells) {
    cells.get_cell_ptr(coord_)->set_player(player_index_);
}
