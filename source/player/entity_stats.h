#include <string>

#pragma once

class PlayersEntitiesStats;

struct EntityStats {
    EntityStats(PlayersEntitiesStats&, std::string);
};

struct UnitStats : public EntityStats {
    unsigned int hp;
    int dmg;
    unsigned int speed;
    int salary;
    UnitStats(PlayersEntitiesStats&, std::string, unsigned int, int, unsigned int, int);
};


struct RangeUnitStats : public UnitStats {
    unsigned int range;
    RangeUnitStats(PlayersEntitiesStats&, std::string, unsigned int, int, unsigned int, int, unsigned int range);
};


struct BuildingStats : public EntityStats {
    bool should_be_destroyed_after_town_destroying;
    BuildingStats(PlayersEntitiesStats&, std::string, bool should_be_destroyed_after_town_destroying);
};

struct BuildingWithHpStats : virtual public BuildingStats {
    unsigned int hp;
    BuildingWithHpStats(PlayersEntitiesStats&, std::string, bool should_be_destroyed_after_town_destroying, unsigned int);
};

struct SuburbBuildingStats : virtual public BuildingStats {
    int income;
    explicit SuburbBuildingStats(PlayersEntitiesStats&, std::string, bool should_be_destroyed_after_town_destroying, int);
};

struct TownStats : public BuildingWithHpStats, public SuburbBuildingStats {
    TownStats(PlayersEntitiesStats&, std::string, unsigned int, int);
};