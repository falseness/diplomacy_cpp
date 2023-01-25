#include "source/drawable_objects/unit/unit.h"

#pragma once


class RangeUnit : virtual public Unit {
public:
    RangeUnit(Cell*, std::string);
    [[nodiscard]] unsigned int get_range() const;
};