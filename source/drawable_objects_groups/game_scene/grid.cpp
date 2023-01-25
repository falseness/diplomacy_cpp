#include "source/drawable_objects_groups/game_scene/grid.h"
#include "source/drawable_objects/cell/cell.h"
#include <tuple>
#include "source/drawable_objects/cell/coord_converter.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/town.h"
#include "source/player/player.h"
#include "source/drawable_objects/building/under_construction/under_construction.h"
#include <cassert>
#include <set>


class GridAction {
    uint8_t action_index;
    std::pair<int, int> coord1;
    std::pair<int, int> coord2;
};


Grid::Grid(Players& players) : logic_helper_(kGridRowsCount, kGridColumnsCount) {
    size_t n = kGridRowsCount;
    size_t m = kGridColumnsCount;
    cells_.resize(n);

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
        for (size_t j = 0; j < m; ++j) {
            int color = 0;
            auto it = colors.find({i, j});
            if (it != colors.end()) {
                color = it->second;
            }
            bool is_suburb = suburbs.find({i, j}) != suburbs.end();
            cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), color, players, is_suburb));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
    cells_[town_poses[0].first + 1][town_poses[0].second]->CreateBuilding<Barrack>("barrack");
    cells_[town_poses[1].first][town_poses[1].second + 1]->CreateBuilding<SuburbBuilding>("farm");
    for (int i = 1; i < players.size(); ++i) {
        std::pair<int, int> town_pos = town_poses[i - 1];
        auto this_player_suburb_cells = get_neighbours(town_pos);
        this_player_suburb_cells.push_back(town_pos);
        cells_[town_pos.first][town_pos.second]->CreateBuilding<Town>("town", this_player_suburb_cells);
        cells_[town_pos.first][town_pos.second]->CreateUnit<Unit>("peasant");
    }

    empty_unit_ = std::make_unique<EmptyUnit>(cells_[0][0].get());
    selected_entity_= empty_unit_.get();
}

bool Grid::HandleClick(SceneInfo& scene, const Vector2D& screen_click_pos, const GameOptions& game_options) {
    Vector2D click_pos = screen_click_pos - game_options.draw_offset;
    if (selected_entity_->is_empty()) {
        std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
        if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()))
            return true;

        selected_entity_ = cells_[coord.first][coord.second]->get_unit_ptr();
        if (selected_entity_->is_empty()) {
            selected_entity_ = cells_[coord.first][coord.second]->get_building_ptr();
        }

        if (!selected_entity_->is_empty())
            selected_entity_->Select(scene);
        return true;
    }
    auto click_response = selected_entity_->HandleClick(scene, click_pos, game_options);

    if (click_response.should_change_selection_to_building_on_same_cell) {
        ChangeSelectedUnitToBuilding();
    }
    else if (click_response.should_remove_selection)
        RemoveSelection();

    if (!selected_entity_->is_empty())
        selected_entity_->Select(scene);

    if (click_response.should_reclick)
        HandleClick(scene, screen_click_pos, game_options);
    return true;
}

size_t Grid::get_rows_count() {
    return cells_.size();
}

size_t Grid::get_columns_count() {
    return cells_[0].size();
}

// order of cells is fixed and it is used in SelectionBorder class
std::vector<std::pair<int, int>> Grid::get_neighbours(std::pair<int, int> coord) const {
    static const std::pair<int, int> neighborhood[2][Grid::kHexagonMaximumNeighbours] = {
            {{0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}, {-1, -1}},
            {{0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}
    };
    std::vector<std::pair<int, int>> result;
    size_t parity = coord.first & 1;
    for (size_t neighbour_number = 0; neighbour_number < Grid::kHexagonMaximumNeighbours; ++neighbour_number) {
        result.emplace_back(coord.first + neighborhood[parity][neighbour_number].first,
                          coord.second + neighborhood[parity][neighbour_number].second);
    }

    return std::move(result);
}

void Grid::MoveUnit(std::pair<int, int> from, std::pair<int, int> to) {
    cells_[from.first][from.second]->MoveUnitTo(*cells_[to.first][to.second]);
}

void Grid::ChangeSelectedUnitToBuilding() {
    assert(selected_entity_ != nullptr);
    auto coord = selected_entity_->get_coord();
    selected_entity_ = cells_[coord.first][coord.second]->get_building_ptr();
}

const size_t Grid::kGridRowsCount = 15;
const size_t Grid::kGridColumnsCount = 6;

void Grid::RemoveSelection() {
    selected_entity_ = empty_unit_.get();
}

bool Grid::is_coord_out_of_range(std::pair<int, int> coord) const {
    return CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size());
}

void Grid::StartProduction(std::pair<int, int> building_position, ProductionInfo production_info) {
    auto barrack = dynamic_cast<Barrack*>(cells_[building_position.first][building_position.second]->
            get_building_ptr());
    assert(barrack);
    barrack->StartProduction(std::move(production_info));
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
