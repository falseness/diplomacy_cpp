#include "entity_factories.h"
#include <source/player/player.h>
#include <source/drawable_objects/cell/cell.h>
#include <cassert>

UnitFactory::UnitFactory(PlayersEntitiesFactories& all_factories, std::string&& unit_name) {
    assert(all_factories.units_production_stats.count(unit_name));
}

void UnitFactory::NextTurn(const Player& player, ProductionInfo& production) const {
    if (get_turns_left(player, production))
        ++production.turns;
}

unsigned int UnitFactory::get_turns_left(const Player& player, const ProductionInfo& production) const {
    return player.get_factories_stats().units_production_stats.find(production.unit_name)->
        second.turns - production.turns;
}

void UnitFactory::CreateUnit(Cell* cell, const ProductionInfo& production) const {
    cell->CreateUnit<Unit>(std::string(production.unit_name));
}

UnitProductionStats::UnitProductionStats(PlayersEntitiesFactories& all_factories, std::string name,
                                         int cost, unsigned int turns) : cost(cost), turns(turns) {
    all_factories.units_production_stats.emplace(std::move(name), *this);
}
