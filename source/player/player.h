#include <map>
#include <source/utility/color.h>
#include <source/player/entity_stats.h>
#include <memory>

#pragma once

struct PlayersEntitiesStats {
    std::map<std::string, EntityStats> entities;
    std::map<std::string, UnitStats> units;
    std::map<std::string, BuildingStats> buildings;
    std::map<std::string, BuildingWithHpStats> buildings_with_hp;
    std::map<std::string, SuburbBuildingStats> suburb_buildings;
};

class Player {
    PlayersEntitiesStats entities_stats_;
public:
    const Color color_;
    explicit Player(const Color&);
    const PlayersEntitiesStats& get_stats() const;
};

