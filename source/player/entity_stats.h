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
    UnitStats(PlayersEntitiesStats&, std::string, unsigned int, int, unsigned int);
};

struct BuildingStats : public EntityStats {
    BuildingStats(PlayersEntitiesStats&, std::string);
};

struct BuildingWithHpStats : public BuildingStats {
    unsigned int hp;
    BuildingWithHpStats(PlayersEntitiesStats&, std::string, unsigned int);
};

struct SuburbBuildingStats : public BuildingStats {
    int income;
    explicit SuburbBuildingStats(PlayersEntitiesStats&, std::string, int);
};
