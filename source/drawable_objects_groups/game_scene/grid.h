#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include "source/options/game.h"
#include <source/player/player.h>
#include <vector>
#include <tuple>
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects/unit/unit.h>
#include <source/drawable_objects/clickable_object.h>
#include "grid_logic_helper.h"

#pragma once


class Players;
class SceneInfo;
class Entity;

class Grid : public DrawableObjectsGroup, public ClickableObject {
    std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
    std::unique_ptr<EmptyUnit> empty_unit_;
    Entity* selected_entity_;
    static const size_t kGridRowsCount;
    static const size_t kGridColumnsCount;
    void ChangeSelectedUnitToBuilding();
public:
    static const uint8_t kHexagonMaximumNeighbours = 6;
    void RemoveSelection();
    [[nodiscard]] std::vector<std::pair<int, int>> get_neighbours(std::pair<int, int> coord) const;
    GridLogicHelper logic_helper_;
    explicit Grid(Players&);
    bool HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void MoveUnit(std::pair<int, int> from, std::pair<int, int> to);
    size_t get_rows_count();
    size_t get_columns_count();
    Grid& operator=(const Grid&) = delete;
    [[nodiscard]] const Cell* get_cell(std::pair<int, int> coord) const;
    [[nodiscard]] Cell* get_cell(std::pair<int, int> coord);
    [[nodiscard]] bool is_coord_out_of_range(std::pair<int, int> coord) const;
};

