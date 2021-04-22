#include <source/drawable_objects/entity.h>
#include <source/player/entity_stats.h>

#pragma once

class Unit : public Entity {
    int dmg_;
    unsigned int moves_;
public:
    static const std::string empty_unit_name_;
    const UnitStats& get_unit_type_stats() const;
    Unit(const Cell&, std::string&&);
};
