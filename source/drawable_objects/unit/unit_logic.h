#include <tuple>
#include <source/drawable_objects/entity.h>

#pragma once

class Unit;
class Grid;

class UnitLogic {
public:
    static void Select(Unit& unit, Grid&);
    // true if should unselect unit
    static ClickResponse ClickLogic(Unit& unit, Grid&, std::pair<int, int> coord);
};