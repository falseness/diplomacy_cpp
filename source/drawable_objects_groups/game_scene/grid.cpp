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
        for (size_t j = 0; j < n; ++j) {
            if (i == j && !i)
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 1, players));
            else
                cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
    cells_[0][0]->CreateUnit<Unit>("peasant");
    //static_cast<std::unique_ptr<Entity>>(std::make_unique<Unit>(cells_[0][0].get(), "peasant"));
    //static_cast<std::unique_ptr<Building>>(std::make_unique<TownStats>(cells_[0][0].get()));
    cells_[0][0]->CreateBuilding<Town>();
    cells_[1][1]->CreateBuilding<Barrack>("barrack");
    selected_entity_ = nullptr;
}

bool Grid::HandleClick(SceneInfo& scene, const Vector2D& screen_click_pos, const GameOptions& game_options) {
    Vector2D click_pos = screen_click_pos - game_options.draw_offset;
    if (selected_entity_ == nullptr) {
        std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
        if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()))
            return true;

        selected_entity_ = cells_[coord.first][coord.second]->get_unit();
        if (selected_entity_ == nullptr) {
            selected_entity_ = cells_[coord.first][coord.second]->get_building();
        }

        if (selected_entity_ != nullptr)
            selected_entity_->Select(scene);
        return true;
    }
    auto click_response = selected_entity_->HandleClick(scene, click_pos, game_options);

    if (click_response.should_change_selection_to_building_on_same_cell) {
        ChangeSelectedUnitToBuilding();
    }
    else if (click_response.should_remove_selection)
        selected_entity_ = nullptr;

    if (selected_entity_ != nullptr)
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

std::vector<std::pair<int, int>> Grid::get_neighbours(std::pair<int, int> coord) {
    static const size_t maximum_neighbour_cells = 6;
    static const std::pair<int, int> neighborhood[2][maximum_neighbour_cells] = {
            {{0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}, {-1, -1}},
            {{0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}
    };
    std::vector<std::pair<int, int>> result;
    size_t parity = coord.first & 1;
    for (size_t neighbour_number = 0; neighbour_number < maximum_neighbour_cells; ++neighbour_number) {
        result.emplace_back(coord.first + neighborhood[parity][neighbour_number].first,
                          coord.second + neighborhood[parity][neighbour_number].second);
        if (CoordConverter::IsCoordOutOfRange(result.back(), cells_.size(), cells_[0].size()))
            result.pop_back();
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


