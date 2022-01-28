#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/cell/cell.h>
#include <tuple>
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>

Grid::Grid(const std::vector<Player>& players) : logic_helper_(kGridRowsCount, kGridColumnsCount) {
    size_t n = kGridRowsCount;
    size_t m = kGridColumnsCount;
    cells_.resize(n);
    for (size_t i = 0; i < cells_.size(); ++i) {
        for (size_t j = 0; j < n; ++j) {
            cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
    cells_[0][0]->CreateUnit<Unit>("peasant");
    selected_entity_ = nullptr;
}

void Grid::HandleClick(SceneInfo& scene, const Vector2D& click_pos, const GameOptions& game_options) {
    // когда-нибудь тут будет нормальный обработчик
    // но пока юнит просто телепортируется
    if (selected_entity_ == nullptr) {
        std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
        if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()) ||
                cells_[coord.first][coord.second]->get_unit() == nullptr)
            return;
        cells_[coord.first][coord.second]->get_unit()->Select(scene);
        selected_entity_ = cells_[coord.first][coord.second]->get_unit();
        return;
    }
    Unit* selected_unit = dynamic_cast<Unit*>(selected_entity_);
    if (selected_unit->HandleClick(scene, click_pos, game_options))
        selected_entity_ = nullptr;
    else
        selected_unit->Select(scene);
    return;
    /*
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()))
        return;

    const Unit* selected_unit = dynamic_cast<const Unit*>(selected_entity_);
    selected_unit.Select();
    std::pair<int, int> unit_coord = selected_unit->get_coord();
    if (unit_coord == coord)
        return;
    cells_[unit_coord.first][unit_coord.second]->MoveUnitTo(*cells_[coord.first][coord.second]);*/
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

const size_t Grid::kGridRowsCount = 15;
const size_t Grid::kGridColumnsCount = 6;
