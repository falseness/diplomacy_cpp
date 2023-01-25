#pragma once

#include <optional>
#include <tuple>

#include <cstdint>

#include "source/player/factories/entity.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects_groups/game_scene/grid/cells.h"

#pragma once

using std::optional;
using std::uint8_t;

class GridAction {
public:
    virtual void PerformAction(GridCells& cells) = 0;
    // can only be used before PerformAction
    virtual std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) = 0;
    virtual ~GridAction() = default;
};

class MoveUnitAction : public GridAction {
    std::pair<int, int> from_;
    std::pair<int, int> to_;
public:
    MoveUnitAction(std::pair<int, int> from, std::pair<int, int> to) : from_(from), to_(to) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class StartProductionAction : public GridAction {
    std::pair<int, int> building_position_;
    ProductionInfo production_info_;
public:
    StartProductionAction(std::pair<int, int> building_position, ProductionInfo production_info) :
        building_position_(building_position), production_info_(std::move(production_info)) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class UndoStartedProductionAction : public GridAction {
    std::pair<int, int> building_position_;
    ProductionInfo production_info_;
public:
    UndoStartedProductionAction(std::pair<int, int> building_position) : building_position_(building_position) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseUnitMovesAction : public GridAction {
    std::pair<int, int> coord_;
    int count_;
public:
    DecreaseUnitMovesAction(std::pair<int, int> coord, int count) : coord_(coord), count_(count) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};


class AddSuburbAction : public GridAction {
    std::pair<int, int> town_coord_;
    std::pair<int, int> new_suburb_coord_;
public:
    AddSuburbAction(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord) : town_coord_(town_coord),
        new_suburb_coord_(new_suburb_coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseUnitHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseUnitHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseBuildingHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseBuildingHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DeleteUnitAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteUnitAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class RestoreLastUnitAction : public GridAction {
    std::pair<int, int> coord_;
public:
    RestoreLastUnitAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};


class DeleteBuildingAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteBuildingAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class RestoreLastBuildingAction : public GridAction {
    std::pair<int, int> coord_;
public:
    RestoreLastBuildingAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DeleteSuburbAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteSuburbAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class RestoreSuburbAction : public GridAction {
    std::pair<int, int> coord_;
public:
    RestoreSuburbAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class SetPlayerAction : public GridAction {
    std::pair<int, int> coord_;
    size_t player_index_;
public:
    SetPlayerAction(std::pair<int, int> coord, size_t player_index) : coord_(coord), player_index_(player_index) {}
    void PerformAction(GridCells& cells) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

template <typename Building>
class CreateBuildingAction : public GridAction {
    std::pair<int, int> coord_;
    ProductionInfo production_info_;
public:
    CreateBuildingAction(std::pair<int, int> coord, ProductionInfo production_info) : coord_(coord),
        production_info_(std::move(production_info)) {}
    void PerformAction(GridCells& cells) override {
        cells.get_cell_ptr(coord_)->template CreateBuilding<Building>(production_info_.name, production_info_);
    }
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override {
        return std::make_unique<DeleteBuildingAction>(coord_);
    }
};

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


