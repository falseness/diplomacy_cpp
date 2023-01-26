#include "catapult_logic.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"


const CatapultUnitLogic CatapultUnitLogic::kCatapultUnitLogic = CatapultUnitLogic();

void CatapultUnitLogic::BFSBodyHandler(const unsigned int max_moves, const Unit &unit, const Grid &grid,
                                       std::deque<std::pair<int, int>> &coords, int moves_count,
                                       std::pair<int, int> new_coord) const {
    get_logic_helper(grid).set_info(new_coord, moves_count + 1);
    coords.push_back(new_coord);
}
