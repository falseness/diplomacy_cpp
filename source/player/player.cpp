#include "player.h"
#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects/building/under_construction/under_construction.h"
#include "source/drawable_objects/building/barrack.h"
#include "source/player/factories/building.h"
#include "source/player/factories/suburb_building.h"


Player::Player(const Color& color) : color_(color) {
    UnitStats(entities_stats_, "peasant", 2, 1, 2);

    UnitStats(entities_stats_, "", 0, 0, 0);
    BuildingStats(entities_stats_, "");

    EntityProductionStats(entities_factories_.units_production_stats, "peasant", 10, 1);
    CreateUnitFactory<UnitFactory>("peasant");

    EntityProductionStats(entities_factories_.buildings_production_stats, "suburb", 1, 0);
    CreateBuildingFactory<SuburbFactory>("suburb");

    EntityProductionStats(entities_factories_.buildings_production_stats, "barrack", 25, 3);
    CreateBuildingFactory<SuburbBuildingFactory<BuildingUnderConstruction<Barrack>>>("barrack");

    EntityProductionStats(entities_factories_.buildings_production_stats, "farm", 24, 2);
    CreateBuildingFactory<SuburbBuildingFactory<BuildingUnderConstruction<SuburbBuilding>>>("farm");

    SuburbBuildingStats(entities_stats_, "barrack", -2);
    SuburbBuildingStats(entities_stats_, "farm", 4);
    TownStats(entities_stats_, "town", 15, 11);
}

const PlayersEntitiesStats& Player::get_stats() const {
    return entities_stats_;
}

void Player::AddUnit(Unit* new_unit) {
    if (!new_unit->is_empty())
        units_.push_back(new_unit);
}

void Player::NextTurn(SceneInfo& scene) {
    // some elements can be deleted in cycle
    auto units_copy = units_;
    for (auto unit : units_copy) {
        unit->NextTurn(scene);
    }
    auto buildings_copy = buildings_;
    for (auto building : buildings_copy) {
        building->NextTurn(scene);
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

Color Player::get_color() const {
    return color_;
}

void Player::DeleteBuilding(Building* building) {
    auto it = std::find(buildings_.begin(), buildings_.end(), building);
    assert(it != buildings_.end());
    buildings_.erase(it);
}

void Player::DeleteUnit(Unit* unit) {
    auto it = std::find(units_.begin(), units_.end(), unit);
    assert(it != units_.end());
    units_.erase(it);
}

