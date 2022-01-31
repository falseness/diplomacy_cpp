#include "entity_factories.h"
#include <source/player/player.h>
#include <source/drawable_objects/cell/cell.h>
#include <cassert>

UnitFactory::UnitFactory(PlayersEntitiesFactories& all_factories, std::string&& unit_name) :
    turn_(0), unit_name_(std::move(unit_name)) {
    assert(all_factories.units_production_stats.count(unit_name_));
}

void UnitFactory::NextTurn(const Player& player) {
    if (get_turns_left(player))
        ++turn_;
}

unsigned int UnitFactory::get_turns_left(const Player& player) const {
    return player.get_factories_stats().units_production_stats.find(unit_name_)->second.turns - turn_;
}

UnitProductionStats::UnitProductionStats(PlayersEntitiesFactories& all_factories, std::string name,
                                         int cost, unsigned int turns) : cost(cost), turns(turns) {
    all_factories.units_production_stats.emplace(std::move(name), *this);
}

void UnitFactory::CreateUnit(Cell* cell) {
    cell->CreateUnit<Unit>(std::string(unit_name_));
}
