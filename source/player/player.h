#include <vector>
#include <map>
#include <source/utility/color.h>
#include <source/player/entity_stats.h>
#include <memory>

#pragma once

class Unit;
class Building;

struct PlayersEntitiesStats {
    std::map<std::string, EntityStats> entities;
    std::map<std::string, UnitStats> units;
    std::map<std::string, BuildingStats> buildings;
    std::map<std::string, BuildingWithHpStats> buildings_with_hp;
    std::map<std::string, SuburbBuildingStats> suburb_buildings;
    std::map<std::string, TownStats> towns;
};

class Player {
    PlayersEntitiesStats entities_stats_;
    std::vector<Unit*> units_;
public:
    void AddUnit(Unit*);
    const Color color_;
    explicit Player(const Color&);
    const PlayersEntitiesStats& get_stats() const;

};

