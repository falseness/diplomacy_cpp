#include "player.h"
#include <source/drawable_objects/unit/unit.h>

Player::Player(const Color& color) : color_(color) {
    UnitStats(entities_stats_, "peasant", 2, 2, 2);
    TownStats(entities_stats_, "town", 15, 11);
}

const PlayersEntitiesStats& Player::get_stats() const {
    return entities_stats_;
}

void Player::AddUnit(Unit* new_unit) {
    units_.push_back(new_unit);
}

void Player::NextTurn() {
    for (auto& unit : units_) {
        unit->NextTurn();
    }
}
