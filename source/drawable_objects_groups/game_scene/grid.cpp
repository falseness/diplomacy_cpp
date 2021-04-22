#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/cell/cell.h>
#include <tuple>
#include <source/drawable_objects/unit/melee/peasant.h>

Grid::Grid(const std::vector<Player>& players) {
    cells_.resize(15);
    for (size_t i = 0; i < cells_.size(); ++i) {
        for (size_t j = 0; j < 6; ++j) {
            cells_[i].push_back(make_unique<Cell>(std::make_pair(i + 2, j + 1), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
    cells_[0][0]->CreateUnit<Peasant>();
}
