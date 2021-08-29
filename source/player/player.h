#include <map>
#include <source/utility/color.h>
#include <source/player/entity_stats.h>

#pragma once

class Player {
    std::map<std::string, UnitStats> units_stats_;
public:
    const Color color_;
    Player(const Color&);
    const UnitStats& get_stats(const std::string&) const;
};