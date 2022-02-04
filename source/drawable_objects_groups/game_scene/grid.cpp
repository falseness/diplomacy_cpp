#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/cell/cell.h>
#include <tuple>
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects/building/town.h>
#include <source/player/player.h>
#include <cassert>

Grid::Grid(Players& players) : logic_helper_(kGridRowsCount, kGridColumnsCount) {

    size_t n = kGridRowsCount;
    size_t m = kGridColumnsCount;
    cells_.resize(n);
    for (size_t i = 0; i < cells_.size(); ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (i == 0 && j == 0)
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 1, players, true));
            else if (i == 1 && j == 1 || i == 0 && j == 1)
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 1, players, true));
            else if (i == 1 && j == 0)
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 2, players));
            else
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }

    empty_unit_ = std::make_unique<EmptyUnit>(cells_[0][0].get());
    selected_entity_= empty_unit_.get();

    cells_[0][1]->CreateUnit<Unit>("peasant");
    cells_[0][0]->CreateBuilding<Town>("town", std::vector<std::pair<int, int>>({{0, 0}, {0, 1}, {1, 0}}));
    cells_[1][1]->CreateBuilding<Barrack>("barrack");
    cells_[1][0]->CreateUnit<Unit>("peasant");
}

bool Grid::HandleClick(SceneInfo& scene, const Vector2D& screen_click_pos, const GameOptions& game_options) {
    Vector2D click_pos = screen_click_pos - game_options.draw_offset;
    if (selected_entity_->is_empty()) {
        std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
        if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()))
            return true;

        selected_entity_ = cells_[coord.first][coord.second]->get_unit();
        if (selected_entity_->is_empty()) {
            selected_entity_ = cells_[coord.first][coord.second]->get_building();
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
    selected_entity_ = cells_[coord.first][coord.second]->get_building();
}

const size_t Grid::kGridRowsCount = 15;
const size_t Grid::kGridColumnsCount = 6;

void Grid::RemoveSelection() {
    selected_entity_ = empty_unit_.get();
}

const Cell* Grid::get_cell(std::pair<int, int> coord) const {
    return cells_[coord.first][coord.second].get();
}

Cell* Grid::get_cell(std::pair<int, int> coord) {
    return cells_[coord.first][coord.second].get();
}

bool Grid::is_coord_out_of_range(std::pair<int, int> coord) const {
    return CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size());
}


