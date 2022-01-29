#include "player.h"

Player::Player(const Color& color) : color_(color) {
    UnitStats(entities_stats_, "peasant", 2, 2, 2);
    SuburbBuildingStats(entities_stats_, "town", 11);
}

const PlayersEntitiesStats& Player::get_stats() const {
    return entities_stats_;
}
