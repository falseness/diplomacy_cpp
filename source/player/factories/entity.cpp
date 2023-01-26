#include "entity.h"

#include <cassert>

#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects/unit/range/range_unit.h"


void EntityFactory::NextTurn(const Player& player, ProductionInfo& production) const {
    if (get_turns_left(player, production))
        ++production.turns;
}

unsigned int UnitFactory::get_turns_left(const Player& player, const ProductionInfo& production) const {
    return player.get_factories_stats().units_production_stats.find(production.name)->
        second.turns - production.turns;
}


UnitFactory::UnitFactory(PlayersEntitiesFactories& all_factories, std::string unit_name) {
    assert(all_factories.units_production_stats.count(unit_name));
}
void UnitFactory::Create(Cell* cell, const ProductionInfo& production) const {
    cell->CreateUnit<Unit>(std::string(production.name));
}


EntityProductionStats::EntityProductionStats(std::map<std::string, EntityProductionStats>& stats, std::string name,
                                             int cost, unsigned int turns) : cost(cost), turns(turns) {
    stats.emplace(std::move(name), *this);
}



