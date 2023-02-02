#include "entity_stats.h"
#include <source/player/player.h>

EntityStats::EntityStats(PlayersEntitiesStats& all_stats, std::string name) {
    all_stats.entities.emplace(std::move(name), *this);
}

UnitStats::UnitStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int dmg, unsigned int speed,
                     int salary) : EntityStats(all_stats, name), hp(hp), dmg(dmg), speed(speed), salary(salary) {
    all_stats.units.emplace(std::move(name), *this);
}

BuildingStats::BuildingStats(PlayersEntitiesStats& all_stats, std::string name) :
    EntityStats(all_stats, name) {
    all_stats.buildings.emplace(std::move(name), *this);
}

BuildingWithHpStats::BuildingWithHpStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp) :
    BuildingStats(all_stats, name), hp(hp) {
    all_stats.buildings_with_hp.emplace(std::move(name), *this);
}

SuburbBuildingStats::SuburbBuildingStats(PlayersEntitiesStats& all_stats, std::string name, int income) :
        BuildingStats(all_stats, name), income(income) {
    all_stats.suburb_buildings.emplace(std::move(name), *this);
}

TownStats::TownStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int income) :
    BuildingWithHpStats(all_stats, name, hp), SuburbBuildingStats(all_stats, name, income),
    BuildingStats(all_stats, name) {
    all_stats.towns.emplace(std::move(name), *this);
}

RangeUnitStats::RangeUnitStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int dmg,
        unsigned int speed, int salary, unsigned int range) : UnitStats(all_stats, name, hp, dmg, speed, salary),
        range(range) {
    all_stats.range_units.emplace(std::move(name), *this);
}
