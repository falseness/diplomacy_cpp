#include "entity_stats.h"
#include <source/player/player.h>

EntityStats::EntityStats(PlayersEntitiesStats& all_stats, std::string name) {
    all_stats.entities.emplace(std::move(name), *this);
}

UnitStats::UnitStats(PlayersEntitiesStats& all_stats, std::string name, unsigned int hp, int dmg, unsigned int speed)
    : EntityStats(all_stats, name), hp(hp), dmg(dmg), speed(speed) {
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
