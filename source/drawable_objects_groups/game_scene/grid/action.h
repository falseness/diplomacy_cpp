#include <optional>
#include <tuple>

#include <cstdint>

#include "source/player/factories/entity.h"
#include "source/drawable_objects_groups/game_scene/grid/cells.h"

#pragma once

using std::optional;
using std::uint8_t;

class GridAction {
public:
    virtual void PerformAction(GridCells& cells) = 0;
    //virtual std::unique_ptr<GridAction> CreateUndoAction() = 0;
    virtual ~GridAction() = default;
};


class StartProductionAction : public GridAction {
    std::pair<int, int> building_position_;
    ProductionInfo production_info_;
public:
    StartProductionAction(std::pair<int, int> building_position, ProductionInfo production_info) :
        building_position_(building_position), production_info_(std::move(production_info)) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

/*
void Grid::MoveUnit(std::pair<int, int> from, std::pair<int, int> to) {
    cells_[from.first][from.second]->MoveUnitTo(*cells_[to.first][to.second]);
}
void Grid::DecreaseUnitMoves(std::pair<int, int> coord, int count) {
    auto unit = cells_[coord.first][coord.second]->get_unit_ptr();
    assert(!unit->is_empty());
    unit->DecreaseMoves(count);
}

void Grid::AddSuburb(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord) {
    auto town = dynamic_cast<Town*>(get_cell_ptr(town_coord)->get_building_ptr());
    assert(town);
    town->AddSuburb(get_cell_ptr(new_suburb_coord).get());
}

void Grid::DecreaseUnitHP(std::pair<int, int> coord, int dmg) {
    get_cell_ptr(coord)->get_unit_ptr()->DecreaseHP(dmg);
}

void Grid::DecreaseBuildingHP(std::pair<int, int> coord, int dmg) {
    dynamic_cast<HittableEntity*>(get_cell_ptr(coord)->get_building_ptr())->DecreaseHP(dmg);
}

void Grid::DeleteUnit(std::pair<int, int> coord) {
    get_cell_ptr(coord)->DeleteUnit();
}

void Grid::DeleteBuilding(std::pair<int, int> coord) {
    get_cell_ptr(coord)->DeleteBuilding();
}

void Grid::DeleteSuburb(std::pair<int, int> coord) {
    get_cell_ptr(coord)->set_suburb(false);
}

void Grid::SetPlayer(std::pair<int, int> coord, size_t player_index) {
    get_cell_ptr(coord)->set_player(player_index);
}
*/

// for savings
struct GridActionJson {
    uint8_t action_index;
    optional<std::pair<int, int>> coord_from;
    optional<std::pair<int, int>> coord_to;
    optional<ProductionInfo> production_info;
    optional<size_t> player_index;
    optional<int> count;

    static const uint8_t kUndoMask = 1 << 7;

    static const uint8_t kMoveUnit = 0;
    static const uint8_t kStartProduction = 1;
    static const uint8_t kDecreaseUnitMoves = 2;
    static const uint8_t kAddSuburb = 3;
    static const uint8_t kDecreaseUnitHP = 4;
    static const uint8_t kDecreaseBuildingHP = 5;
    static const uint8_t kDeleteUnit = 6;
    static const uint8_t kDeleteBuilding = 7;
    static const uint8_t kDeleteSuburb = 8;
    static const uint8_t kSetPlayer = 9;
};

class Entity;
class Grid;

struct SelectedEntity {
    std::pair<int, int> coord;
    bool is_unit;
};


