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

class MoveUnitAction : public GridAction {
    std::pair<int, int> from_;
    std::pair<int, int> to_;
public:
    MoveUnitAction(std::pair<int, int> from, std::pair<int, int> to) : from_(from), to_(to) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class DecreaseUnitMovesAction : public GridAction {
    std::pair<int, int> coord_;
    int count_;
public:
    DecreaseUnitMovesAction(std::pair<int, int> coord, int count) : coord_(coord), count_(count) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};


class AddSuburbAction : public GridAction {
    std::pair<int, int> town_coord_;
    std::pair<int, int> new_suburb_coord_;
public:
    AddSuburbAction(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord) : town_coord_(town_coord),
        new_suburb_coord_(new_suburb_coord) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class DecreaseUnitHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseUnitHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class DecreaseBuildingHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseBuildingHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class DeleteUnitAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteUnitAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};


class DeleteBuildingAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteBuildingAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class DeleteSuburbAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteSuburbAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};

class SetPlayerAction : public GridAction {
    std::pair<int, int> coord_;
    size_t player_index_;
public:
    SetPlayerAction(std::pair<int, int> coord, size_t player_index) : coord_(coord), player_index_(player_index) {}
    void PerformAction(GridCells& cells) override;
    //std::unique_ptr<GridAction> CreateUndoAction()
};
/*

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


