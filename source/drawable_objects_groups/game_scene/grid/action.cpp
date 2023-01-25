#include "action.h"

#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects/cell/cell.h"


void StartProductionAction::PerformAction(GridCells &cells) {
    auto barrack = dynamic_cast<Barrack*>(cells.get_cell_ptr(building_position_)->get_building_ptr());
    assert(barrack);
    barrack->StartProduction(std::move(production_info_));
}