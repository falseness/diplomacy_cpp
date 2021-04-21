#include <source/sprites_groups/game_scene/grid.h>
#include <source/sprites/cell/cell.h>
#include <tuple>

Grid::Grid(const GameOptions& game_options) {
    cells_.resize(20);
    for (size_t i = 0; i < 20; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            cells_[i].push_back(make_unique<Cell>(std::make_pair(i + 3, j + 1), game_options));
            sprites_.push_back(cells_[i][j].get());
        }
    }
}
