#pragma once

#include "source/player/factories/building_and_suburb.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/town.h"


template <typename Building>
class BuildingFactory : public BuildingAndSuburbFactory {
protected:
    std::string name_;
public:
    BuildingFactory(PlayersEntitiesFactories &all_factories, std::string names);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&, const Town* town) const override;
};


template <typename Building>
ClickResponse BuildingFactory<Building>::HandleClick(SceneInfo &scene, const Vector2D &click_pos,
                                           const GameOptions &game_options, const Town* town) const {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    auto cell = scene.grid.get_cell(coord);
    if (!is_correct_click(scene, coord) || !cell->get_building()->is_empty())
        return {true, false, false};

    unsigned int turns = town->get_player().get_factories_stats().buildings_production_stats.find(name_)->second.turns;

    scene.grid.CreateBuilding<Building>(coord, std::move(ProductionInfo{name_, turns}));
    scene.town_production_interface.ReClick(scene);
    return {false, false, false};
}

template <typename Building>
BuildingFactory<Building>::BuildingFactory(PlayersEntitiesFactories &all_factories, std::string name) :
    BuildingAndSuburbFactory(all_factories, name), name_(std::move(name)) {}