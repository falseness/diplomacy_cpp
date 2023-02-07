#include "cells.h"

#include "source/drawable_objects/cell/cell.h"

#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/cell/coord_converter.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/town.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/game_scene/grid/action.h"
#include "source/drawable_objects/unit/range/range_unit.h"
#include "source/drawable_objects/building/nature.h"


bool GridCells::is_coord_out_of_range(std::pair<int, int> coord) const {
    return CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size());
}

std::vector<std::pair<int, int>> GridCells::get_neighbours(std::pair<int, int> coord) const {
    static const std::pair<int, int> neighborhood[2][GridCells::kHexagonMaximumNeighbours] = {
            {{0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}, {-1, -1}},
            {{0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}
    };
    std::vector<std::pair<int, int>> result;
    size_t parity = coord.first & 1;
    for (size_t neighbour_number = 0; neighbour_number < GridCells::kHexagonMaximumNeighbours; ++neighbour_number) {
        result.emplace_back(coord.first + neighborhood[parity][neighbour_number].first,
                            coord.second + neighborhood[parity][neighbour_number].second);
    }

    return std::move(result);
}

GridCells::GridCells(size_t rows_count, size_t columns_count, Players& players) {
    cells_.resize(rows_count);

    std::map<std::pair<int, int>, int> colors;
    std::set<std::pair<int, int>> suburbs;

    std::pair<int, int> town_poses[2] = {{1, 1}, {8, 3}};
    for (int i = 1; i < players.size(); ++i) {
        std::pair<int, int> town_pos = town_poses[i - 1];
        auto this_player_suburb_cells = get_neighbours(town_pos);
        this_player_suburb_cells.push_back(town_pos);

        for (auto u: this_player_suburb_cells) {
            colors.emplace(u, i);
            suburbs.emplace(u);
        }
    }
    colors.emplace(std::pair<int, int>{2, 3}, 1);
    colors.emplace(std::pair<int, int>{9, 4}, 2);

    for (size_t i = 0; i < cells_.size(); ++i) {
        for (size_t j = 0; j < columns_count; ++j) {
            int color = 0;
            auto it = colors.find({i, j});
            if (it != colors.end()) {
                color = it->second;
            }
            bool is_suburb = suburbs.find({i, j}) != suburbs.end();
            cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), color, players, is_suburb));
        }
    }

    cells_[4][2]->CreateBuilding<NaturalBuilding>("lake");
    cells_[4][4]->CreateBuilding<Mountain>("mountain");
    cells_[town_poses[0].first + 1][town_poses[0].second]->CreateBuilding<Barrack>("barrack");
    cells_[town_poses[1].first][town_poses[1].second + 1]->CreateBuilding<SuburbBuilding>("farm");
    for (int i = 1; i < players.size(); ++i) {
        std::pair<int, int> town_pos = town_poses[i - 1];
        auto this_player_suburb_cells = get_neighbours(town_pos);
        this_player_suburb_cells.push_back(town_pos);
        cells_[town_pos.first][town_pos.second]->CreateBuilding<Town>("town",
            std::set(this_player_suburb_cells.begin(), this_player_suburb_cells.end()));
        cells_[town_pos.first][town_pos.second]->CreateUnit<RangeUnit>("archer");
    }
}
