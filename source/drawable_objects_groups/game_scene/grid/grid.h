#include <vector>
#include <tuple>

#include "source/drawable_objects_groups/drawable_objects_group.h"
#include "source/sfml_facades/screen.h"
#include "source/options/game.h"

#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/clickable_object.h"
#include "source/drawable_objects_groups/game_scene/grid_logic_helper.h"
#include "source/drawable_objects_groups/game_scene/grid/action.h"
#include "source/drawable_objects_groups/game_scene/undo_button.h"
#include "cells.h"

#pragma once


class Players;
class SceneInfo;
class Entity;

class Grid : public DrawableObjectsGroup, public ClickableObject {
    UndoButton undo_button_;
    GridCells grid_cells_;
    std::unique_ptr<EmptyUnit> empty_unit_;
    Entity* selected_entity_;
    static const size_t kGridRowsCount;
    static const size_t kGridColumnsCount;
    void ChangeSelectedUnitToBuilding();
    [[nodiscard]] inline std::unique_ptr<Cell>& get_cell_ptr(const std::pair<int, int> coord) {
        return grid_cells_.get_cell_ptr(coord);
    }
public:
    static const uint8_t kHexagonMaximumNeighbours = 6;
    void RemoveSelection();
    [[nodiscard]] std::vector<std::pair<int, int>> get_neighbours(std::pair<int, int> coord) const;
    mutable GridLogicHelper logic_helper_;
    mutable GridLogicHelper additional_logic_helper_;
    explicit Grid(Players&);
    void PerformActionAndSaveUndo(GridAction& action);
    void PerformAction(GridAction& action);
    bool HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void MoveUnit(std::pair<int, int> from, std::pair<int, int> to);
    void StartProduction(std::pair<int, int> building_position, ProductionInfo production_info);
    void DecreaseUnitMoves(std::pair<int, int> coord, int count);
    void AddSuburb(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord);
    void DecreaseUnitHP(std::pair<int, int> coord, int dmg);
    void DecreaseBuildingHP(std::pair<int, int> coord, int dmg);
    void DeleteUnit(std::pair<int, int> coord);
    void DeleteBuilding(std::pair<int, int> coord);
    void DeleteSuburb(std::pair<int, int> coord);
    void SetPlayer(std::pair<int, int> coord, size_t player_index);
    [[nodiscard]] inline size_t get_rows_count() const {
        return grid_cells_.get_rows_count();
    }
    [[nodiscard]] inline size_t get_columns_count() const {
        return grid_cells_.get_columns_count();
    }
    Grid& operator=(const Grid&) = delete;
    [[nodiscard]] inline const Cell *get_cell(const std::pair<int, int> coord) const {
        return grid_cells_.get_cell(coord);
    }
    [[nodiscard]] inline bool is_coord_out_of_range(std::pair<int, int> coord) const {
        return grid_cells_.is_coord_out_of_range(coord);
    }
    template <typename Building>
    void CreateBuilding(std::pair<int, int> coord, ProductionInfo production_info) {
        CreateBuildingAction<Building> action(coord, std::move(production_info));
        PerformActionAndSaveUndo(action);
    }
    void ClearUndoStack();
    void StartUndoSequence();
    void HandleKeyPress(SceneInfo& scene);
    void SelectUnit(std::pair<int, int> coord, SceneInfo& scene);
    void SelectBuilding(std::pair<int, int> coord, SceneInfo& scene);
    [[nodiscard]] Vector2D get_right_bottom_corner(const GameOptions& game_options) const;
};

