#include <tuple>

#pragma once

class Unit;
class Grid;

class UnitLogic {
public:
    static void Select(Unit* unit, Grid*);
    // true if should unselect unit
    static bool ClickLogic(Unit* unit, Grid*, std::pair<int, int> coord);
};