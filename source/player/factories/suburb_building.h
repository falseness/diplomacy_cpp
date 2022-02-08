#include "source/player/factories/building.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid.h"
#include "source/drawable_objects/building/town.h"

#pragma once

template <typename Building>
class SuburbBuildingFactory : public BuildingFactory {
    void BFSBody(
            std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
            std::deque<std::pair<int, int>>& coords, int distance,
            const std::pair<int, int>& neighbour) const override;
    std::string name_;
public:
    SuburbBuildingFactory(PlayersEntitiesFactories& all_factories, std::string);
    ClickResponse HandleClick(SceneInfo& scene, const Vector2D& click_pos, const GameOptions& game_option,
                              Town* town) override;
};

template <typename Building>
void SuburbBuildingFactory<Building>::BFSBody(std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
                                              std::deque<std::pair<int, int>>& coords, int distance,
                                              const std::pair<int, int>& neighbour) const {
    if (!grid.logic_helper_.is_visited(neighbour))
        return;
    visited_cells.push_back(neighbour);
    grid.logic_helper_.set_info(neighbour, distance + 1);
    coords.push_back(neighbour);
}

template <typename Building>
ClickResponse SuburbBuildingFactory<Building>::HandleClick(
        SceneInfo& scene, const Vector2D& click_pos, const GameOptions& game_options, Town *town) {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    auto cell = scene.grid.get_cell(coord);
    if (!is_correct_click(scene, coord) || !cell->get_building()->is_empty())
        return {true, false, false};
    unsigned int turns = town->get_player().get_factories_stats().buildings_production_stats.find(name_)->second.turns;
    cell->template CreateBuilding<Building>(name_, ProductionInfo{name_, turns});
    scene.town_production_interface.ReClick(scene);
    return {false, false, false};
}

template <typename Building>
SuburbBuildingFactory<Building>::SuburbBuildingFactory(PlayersEntitiesFactories &all_factories, std::string name) :
        BuildingFactory(all_factories, name), name_(std::move(name)) {}