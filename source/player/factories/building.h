#pragma once

#include "source/player/factories/building_and_suburb.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/town.h"
#include "source/utility/map_additional_functions.h"


template <typename Building>
class BuildingFactory : public BuildingAndSuburbFactory {
    [[nodiscard]] inline const EntityProductionStats& get_production_stats(const Player& player) const {
        return safe_find(player.get_factories_stats().buildings_production_stats, name_);
    }
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

    size_t player_index = town->get_player_index();
    const EntityProductionStats& production_stats = get_production_stats(town->get_player());
    unsigned int turns = production_stats.turns;

    scene.grid.CreateBuilding<Building>(coord, std::move(ProductionInfo{name_, turns}));
    scene.grid.IncreaseGold(player_index, -production_stats.cost);

    scene.town_production_interface.ReClick(scene);
    return {false, false, false};
}

template <typename Building>
BuildingFactory<Building>::BuildingFactory(PlayersEntitiesFactories &all_factories, std::string name) :
    BuildingAndSuburbFactory(all_factories, name), name_(std::move(name)) {}