#include <vector>
#include <tuple>

class GridLogicHelper {
    int counter_;
    std::vector<std::vector<int>> occupied_cells_;
    std::vector<std::vector<int>> cells_info_;
    static const int kCellInitializationValue;
public:
    GridLogicHelper(size_t grid_rows_count, size_t grid_columns_count);
    void increment_counter();
    bool is_occupied(std::pair<size_t, size_t>);
    void occupy(std::pair<size_t, size_t>);
    int get_info(std::pair<size_t, size_t>);
    void set_info(std::pair<size_t, size_t>, int value);
};
