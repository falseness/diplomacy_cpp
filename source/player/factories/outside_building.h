#include "source/player/factories/building_and_suburb.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/building/town.h"
#include "source/player/factories/building.h"

#pragma once

template <typename Building>
class OutsideBuilding : public BuildingFactory<Building> {
    void BFSBody(
            std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
            std::deque<std::pair<int, int>>& coords, int distance,
            const std::pair<int, int>& neighbour) const override;
};

template <typename Building>
void OutsideBuilding<Building>::BFSBody(std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
                                        std::deque<std::pair<int, int>>& coords, int distance,
                                        const std::pair<int, int>& neighbour) const {
    visited_cells.push_back(neighbour);
    grid.logic_helper_.set_info(neighbour, distance + 1);
    coords.push_back(neighbour);
}




