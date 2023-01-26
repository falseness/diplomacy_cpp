#include "source/drawable_objects/unit/range/range_unit_logic.h"


class CatapultUnitLogic : public RangeUnitLogic {
    [[nodiscard]] inline bool CellSkipCondition(const Cell &, const Unit &unit) const override {
        return false;
    }
    void BFSBodyHandler(const unsigned int max_moves, const Unit &unit, const Grid &grid,
                        std::deque<std::pair<int, int>> &coords, int moves_count, std::pair<int, int> new_coord) const override;
public:
    static const CatapultUnitLogic kCatapultUnitLogic;
};