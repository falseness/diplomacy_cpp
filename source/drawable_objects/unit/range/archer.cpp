#include "archer.h"
#include "source/player/player.h"

RangeUnit::RangeUnit(Cell* cell, std::string name) : Unit(cell, name), Entity(cell, std::move(name)) {

}

unsigned int RangeUnit::get_range() const {
    auto it = get_player_stats().range_units.find(image_name_);
    assert(it != get_player_stats().range_units.end());
    return it->second.range;
}
