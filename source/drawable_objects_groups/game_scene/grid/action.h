#pragma once

#include <optional>
#include <tuple>

#include <cstdint>

#include "source/player/player.h"
#include "source/player/factories/entity.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects_groups/game_scene/grid/cells.h"

using std::optional;
using std::uint8_t;

class GridAction {
public:
    virtual void PerformAction(GridCells &cells, Players &players) = 0;
    // can only be used before PerformAction
    virtual std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) = 0;
    virtual ~GridAction() = default;
};

class MoveUnitAction : public GridAction {
    std::pair<int, int> from_;
    std::pair<int, int> to_;
public:
    MoveUnitAction(std::pair<int, int> from, std::pair<int, int> to) : from_(from), to_(to) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class StartProductionAction : public GridAction {
    std::pair<int, int> building_position_;
    ProductionInfo production_info_;
public:
    StartProductionAction(std::pair<int, int> building_position, ProductionInfo production_info) :
        building_position_(building_position), production_info_(std::move(production_info)) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class UndoStartedProductionAction : public GridAction {
    std::pair<int, int> building_position_;
    ProductionInfo production_info_;
public:
    UndoStartedProductionAction(std::pair<int, int> building_position) : building_position_(building_position) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseUnitMovesAction : public GridAction {
    std::pair<int, int> coord_;
    int count_;
public:
    DecreaseUnitMovesAction(std::pair<int, int> coord, int count) : coord_(coord), count_(count) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};


class AddSuburbAction : public GridAction {
    std::pair<int, int> town_coord_;
    std::pair<int, int> new_suburb_coord_;
public:
    AddSuburbAction(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord) : town_coord_(town_coord),
        new_suburb_coord_(new_suburb_coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseUnitHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseUnitHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DecreaseBuildingHPAction : public GridAction {
    std::pair<int, int> coord_;
    int dmg_;
public:
    DecreaseBuildingHPAction(std::pair<int, int> coord, int dmg) : coord_(coord), dmg_(dmg) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DeleteUnitAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteUnitAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class RestoreLastUnitAction : public GridAction {
    std::pair<int, int> coord_;
public:
    RestoreLastUnitAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};


class DeleteBuildingAction : public GridAction {
    std::pair<int, int> coord_;
public:
    DeleteBuildingAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class RestoreLastBuildingAction : public GridAction {
    std::pair<int, int> coord_;
public:
    RestoreLastBuildingAction(std::pair<int, int> coord) : coord_(coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class DeleteSuburbAction : public GridAction {
    std::pair<int, int> town_coord_;
    std::pair<int, int> suburb_coord_;
public:
    DeleteSuburbAction(std::pair<int, int> town_coord, std::pair<int, int> coord) : town_coord_(town_coord),
                                                                                    suburb_coord_(coord) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};

class SetPlayerAction : public GridAction {
    std::pair<int, int> coord_;
    size_t player_index_;
public:
    SetPlayerAction(std::pair<int, int> coord, size_t player_index) : coord_(coord), player_index_(player_index) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
};


using std::forward; // You can change this if you like unreadable code or care hugely about namespace pollution.

template<size_t N>
struct ApplyMember
{
    template<typename C, typename F, typename T, typename... A>
    static inline auto apply(C&& c, F&& f, T&& t, A&&... a) ->
    decltype(ApplyMember<N-1>::apply(forward<C>(c), forward<F>(f), forward<T>(t), std::get<N-1>(forward<T>(t)), forward<A>(a)...))
    {
        return ApplyMember<N-1>::apply(forward<C>(c), forward<F>(f), forward<T>(t), std::get<N-1>(forward<T>(t)), forward<A>(a)...);
    }
};

template<>
struct ApplyMember<0>
{
    template<typename C, typename F, typename T, typename... A>
    static inline auto apply(C&& c, F&& f, T&&, A&&... a) ->
    decltype((forward<C>(c)->*forward<F>(f))(forward<A>(a)...))
    {
        return (forward<C>(c)->*forward<F>(f))(forward<A>(a)...);
    }
};

// C is the class, F is the member function, T is the tuple.
template<typename C, typename F, typename T>
inline auto apply(C&& c, F&& f, T&& t) ->
decltype(ApplyMember<std::tuple_size<typename std::decay<T>::type>::value>::apply(forward<C>(c), forward<F>(f), forward<T>(t)))
{
    return ApplyMember<std::tuple_size<typename std::decay<T>::type>::value>::apply(forward<C>(c), forward<F>(f), forward<T>(t));
}

template <typename Building, typename... Args>
class CreateBuildingAction : public GridAction {
    std::pair<int, int> coord_;
    std::tuple<Args...> args;
public:
    CreateBuildingAction(std::pair<int, int> coord, Args&&... args) : coord_(coord), args(std::forward<Args>(args)...) {}
    void PerformAction(GridCells &cells, Players&) override {
        apply(static_cast<Cell*>(cells.get_cell_ptr(coord_).get()), &Cell::CreateBuilding<Building, Args...>, std::move(args));
    }
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override {
        return std::make_unique<DeleteBuildingAction>(coord_);
    }
};

class IncreasePlayersGold : public GridAction {
    size_t player_index_;
    // may be negative
    int gold_increase_;
public:
    IncreasePlayersGold(size_t player_index, int gold_increase) : player_index_(player_index),
        gold_increase_(gold_increase ) {}
    void PerformAction(GridCells &cells, Players &players) override;
    std::unique_ptr<GridAction> CreateUndoAction(GridCells& cells) override;
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


