#include "grid_logic_helper.h"

void GridLogicHelper::increment_counter() {
    ++counter_;
}

bool GridLogicHelper::is_occupied(std::pair<size_t, size_t> coord) {
    return occupied_cells_[coord.first][coord.second] == counter_;
}

GridLogicHelper::GridLogicHelper(size_t grid_rows_count, size_t grid_columns_count) {
    occupied_cells_.resize(grid_columns_count);
    cells_info_.resize(grid_columns_count);
    for (auto& row : occupied_cells_) {
        row.resize(grid_columns_count, kCellInitializationValue);
    }
    for (auto& row : cells_info_) {
        row.resize(grid_columns_count, kCellInitializationValue);
    }
}

void GridLogicHelper::set_info(std::pair<size_t, size_t> coord, int value) {
    cells_info_[coord.first][coord.second] = value;
}

int GridLogicHelper::get_info(std::pair<size_t, size_t> coord) {
    return cells_info_[coord.first][coord.second];
}

void GridLogicHelper::occupy(std::pair<size_t, size_t> coord) {
    occupied_cells_[coord.first][coord.second] = counter_;
}
const int GridLogicHelper::kCellInitializationValue = 0;