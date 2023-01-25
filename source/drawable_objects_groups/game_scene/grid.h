#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/sfml_facades/screen.h>
#include "source/options/game.h"
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
    [[nodiscard]] inline std::unique_ptr<Cell>& get_cell_ptr(const std::pair<int, int> coord) {
        assert(!is_coord_out_of_range(coord));
        return cells_[coord.first][coord.second];
    }
public:
    static const uint8_t kHexagonMaximumNeighbours = 6;
    void RemoveSelection();
    [[nodiscard]] std::vector<std::pair<int, int>> get_neighbours(std::pair<int, int> coord) const;
    mutable GridLogicHelper logic_helper_;
    explicit Grid(Players&);
    bool HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void MoveUnit(std::pair<int, int> from, std::pair<int, int> to);
    void StartProduction(std::pair<int, int> building_position, ProductionInfo production_info);
    void DecreaseUnitMoves(std::pair<int, int> coord, int count);
    void AddSuburb(std::pair<int, int> town_coord, std::pair<int, int> new_suburb_coord);
    void DecreaseUnitHP(std::pair<int, int> coord, int dmg);
    void DecreaseBuildingHP(std::pair<int, int> coord, int dmg);
    void DeleteUnit(std::pair<int, int> coord);
    void DeleteBuilding(std::pair<int, int> coord);
    size_t get_rows_count();
    size_t get_columns_count();
    Grid& operator=(const Grid&) = delete;
    [[nodiscard]] inline const Cell* get_cell(const std::pair<int, int> coord) const {
        assert(!is_coord_out_of_range(coord));
        return cells_[coord.first][coord.second].get();
    }
    [[nodiscard]] bool is_coord_out_of_range(std::pair<int, int> coord) const;

    template <typename Building>
    void CreateBuilding(std::pair<int, int> coord, ProductionInfo production_info) {
        get_cell_ptr(coord)->template CreateBuilding<Building>(production_info.name, production_info);
    }
};

