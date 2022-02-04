#include "grid_logic_helper.h"
#include <cassert>

void GridLogicHelper::increment_counter() {
    ++counter_;
}

bool GridLogicHelper::is_visited(std::pair<size_t, size_t> coord) const {
    return visited_cells_[coord.first][coord.second] == counter_;
}

GridLogicHelper::GridLogicHelper(size_t grid_rows_count, size_t grid_columns_count) {
    counter_ = kCellInitializationValue;

    visited_cells_.resize(grid_rows_count);
    cells_info_.resize(grid_rows_count);
    cells_parent_.resize(grid_rows_count);
    for (auto& row : visited_cells_) {
        row.resize(grid_columns_count, kCellInitializationValue);
    }
    for (auto& row : cells_info_) {
        row.resize(grid_columns_count, kCellInitializationValue);
    }
    for (auto& row : cells_parent_) {
        row.resize(grid_columns_count);
    }
}

void GridLogicHelper::set_info(std::pair<size_t, size_t> coord, int value) {
    assert(is_visited(coord));
    cells_info_[coord.first][coord.second] = value;
}

int GridLogicHelper::get_info(std::pair<size_t, size_t> coord) {
    assert(is_visited(coord));
    return cells_info_[coord.first][coord.second];
}

void GridLogicHelper::visit(std::pair<size_t, size_t> coord) {
    visited_cells_[coord.first][coord.second] = counter_;
}
const int GridLogicHelper::kCellInitializationValue = 0;

std::pair<size_t, size_t> GridLogicHelper::get_parent(std::pair<size_t, size_t> coord) {
    assert(is_visited(coord));
    return cells_parent_[coord.first][coord.second];
}

void GridLogicHelper::set_parent(std::pair<size_t, size_t> coord, std::pair<size_t, size_t> parent) {
    assert(is_visited(coord));
    cells_parent_[coord.first][coord.second] = parent;
}
