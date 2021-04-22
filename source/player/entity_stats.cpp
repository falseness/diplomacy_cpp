#include "entity_stats.h"

EntityStats::EntityStats(unsigned int hp) : hp(hp) {}

UnitStats::UnitStats(unsigned int hp, int dmg, unsigned int speed) : EntityStats(hp), dmg(dmg), speed(speed) {}