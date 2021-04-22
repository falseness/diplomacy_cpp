#pragma once

struct EntityStats {
    unsigned int hp;
    EntityStats(unsigned int);
};

struct UnitStats : public EntityStats {
    int dmg;
    unsigned int speed;
    UnitStats(unsigned int, int, unsigned int);
};