#pragma once

#include <vector>
#include <tuple>

class GridLogicHelper {
    int counter_;
    std::vector<std::vector<int>> visited_cells_;
    std::vector<std::vector<int>> cells_info_;
    std::vector<std::vector<std::pair<int, int>>> cells_parent_;
    static const int kCellInitializationValue;
public:
    GridLogicHelper(size_t grid_rows_count, size_t grid_columns_count);
    void increment_counter();
    [[nodiscard]] bool is_visited(std::pair<size_t, size_t>) const;
    void visit(std::pair<size_t, size_t>);
    int get_info(std::pair<size_t, size_t>);
    void set_info(std::pair<size_t, size_t>, int value);
    std::pair<size_t, size_t> get_parent(std::pair<size_t, size_t>);
    void set_parent(std::pair<size_t, size_t>, std::pair<size_t, size_t>);
};
