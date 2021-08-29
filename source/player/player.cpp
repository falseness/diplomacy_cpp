#include "player.h"

Player::Player(const Color& color) : color_(color), units_stats_(
        {
            {"peasant", UnitStats(2, 2, 2)}
        }) {}

const UnitStats& Player::get_stats(const std::string& unit_name) const {
    auto it = units_stats_.find(unit_name);
    if (it == units_stats_.end())
        throw std::out_of_range("unit not found");
    return it->second;
}