#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/cell/cell.h>
#include <tuple>
#include <source/drawable_objects/cell/coord_converter.h>
#include <iostream>

Grid::Grid(const std::vector<Player>& players) {
    cells_.resize(15);
    for (size_t i = 0; i < cells_.size(); ++i) {
        for (size_t j = 0; j < 6; ++j) {
            cells_[i].push_back(std::make_unique<Cell>(std::make_pair(i, j), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
    cells_[0][0]->CreateUnit<Unit>("peasant");
    selected_entity_ = cells_[0][0]->get_unit();
}

void Grid::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    // когда-нибудь тут будет нормальный обработчик
    // но пока юнит просто телепортируется

    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    if (CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size()))
        return;
    const Unit* selected_unit = dynamic_cast<const Unit*>(selected_entity_);
    std::pair<int, int> unit_coord = selected_unit->get_coord();
    if (unit_coord == coord)
        return;
    cells_[unit_coord.first][unit_coord.second]->MoveUnitTo(*cells_[coord.first][coord.second]);
}
