#include "player.h"
#include <source/drawable_objects/unit/unit.h>
#include <source/drawable_objects/building/building.h>

Player::Player(const Color& color) : color_(color) {
    UnitStats(entities_stats_, "peasant", 2, 2, 2);

    UnitStats(entities_stats_, "", 0, 0, 0);
    BuildingStats(entities_stats_, "");

    UnitProductionStats(entities_factories_, "peasant", 10, 1);
    CreateUnitFactory<UnitFactory>("peasant");

    SuburbBuildingStats(entities_stats_, "barrack", -2);
    TownStats(entities_stats_, "town", 15, 11);
}

const PlayersEntitiesStats& Player::get_stats() const {
    return entities_stats_;
}

void Player::AddUnit(Unit* new_unit) {
    if (!new_unit->is_empty())
        units_.push_back(new_unit);
}

void Player::NextTurn() {
    for (auto unit : units_) {
        unit->NextTurn();
    }
    for (auto building : buildings_) {
        building->NextTurn();
    }
}

const PlayersEntitiesFactories& Player::get_factories_stats() const {
    return entities_factories_;
}

int Player::get_gold() const {
    return gold_;
}

void Player::AddBuilding(Building* building) {

    buildings_.push_back(building);
}

