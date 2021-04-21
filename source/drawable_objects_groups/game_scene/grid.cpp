#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/cell/cell.h>
#include <tuple>

Grid::Grid(const std::vector<Player>& players) {
    cells_.resize(20);
    for (size_t i = 0; i < 20; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            cells_[i].push_back(make_unique<Cell>(std::make_pair(i + 3, j + 1), 0, players));

            drawable_objects_.push_back(cells_[i][j].get());
        }
    }
}
