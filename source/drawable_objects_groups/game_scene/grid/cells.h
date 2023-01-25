#pragma once

#include <cassert>

#include <vector>
#include <memory>


class Cell;

class GridCells {
    std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
public:
    [[nodiscard]] inline std::unique_ptr<Cell>& get_cell_ptr(const std::pair<int, int> coord) {
        assert(!is_coord_out_of_range(coord));
        return cells_[coord.first][coord.second];
    }
    [[nodiscard]] inline const Cell* get_cell(const std::pair<int, int> coord) const {
        assert(!is_coord_out_of_range(coord));
        return cells_[coord.first][coord.second].get();
    }
    [[nodiscard]] bool is_coord_out_of_range(std::pair<int, int> coord) const;

    [[nodiscard]] inline size_t get_rows_count() const {
        return cells_.size();
    }

    [[nodiscard]] inline size_t get_columns_count() const {
        return cells_[0].size();
    }

    // temporary method. refactoring is needed
    [[nodiscard]] inline std::vector<std::vector<std::unique_ptr<Cell>>>& get_cells() {
        return cells_;
    }
    GridCells() = default;
};