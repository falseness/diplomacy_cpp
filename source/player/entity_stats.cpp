#include "entity_stats.h"
#include <source/player/player.h>

EntityStats::EntityStats(PlayersEntitiesStats& all_stats, std::string name) {
    all_stats.entities.emplace(std::move(name), *this);
}

UnitStats::UnitStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int dmg, unsigned int speed,
                     int salary) : EntityStats(all_stats, name), hp(hp), dmg(dmg), speed(speed), salary(salary) {
    all_stats.units.emplace(std::move(name), *this);
}

BuildingStats::BuildingStats(PlayersEntitiesStats& all_stats, std::string name, bool should_be_destroyed_after_town_destroying) :
    EntityStats(all_stats, name), should_be_destroyed_after_town_destroying(should_be_destroyed_after_town_destroying) {
    all_stats.buildings.emplace(std::move(name), *this);
}

BuildingWithHpStats::BuildingWithHpStats(PlayersEntitiesStats& all_stats, std::string name, bool should_be_destroyed_after_town_destroying, unsigned int hp) :
    BuildingStats(all_stats, name, should_be_destroyed_after_town_destroying), hp(hp) {
    all_stats.buildings_with_hp.emplace(std::move(name), *this);
}

SuburbBuildingStats::SuburbBuildingStats(PlayersEntitiesStats& all_stats, std::string name, bool should_be_destroyed_after_town_destroying, int income) :
        BuildingStats(all_stats, name, should_be_destroyed_after_town_destroying), income(income) {
    all_stats.suburb_buildings.emplace(std::move(name), *this);
}

TownStats::TownStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int income) :
    BuildingWithHpStats(all_stats, name, false, hp), SuburbBuildingStats(all_stats, name, false, income),
    BuildingStats(all_stats, name, false) {
    all_stats.towns.emplace(std::move(name), *this);
}

RangeUnitStats::RangeUnitStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int dmg,
        unsigned int speed, int salary, unsigned int range) : UnitStats(all_stats, name, hp, dmg, speed, salary),
        range(range) {
    all_stats.range_units.emplace(std::move(name), *this);
}
