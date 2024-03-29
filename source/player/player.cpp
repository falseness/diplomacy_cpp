#include "player.h"
#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects/building/under_construction/under_construction.h"
#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects/building/outside_building.h"
#include "source/player/factories/building_and_suburb.h"
#include "source/player/factories/suburb_building.h"
#include "source/player/factories/outside_building.h"
#include "source/player/factories/range_unit.h"
#include "source/drawable_objects/unit/range/range_unit.h"
#include "source/drawable_objects/unit/range/catapult.h"


Player::Player(const Color& color) : color_(color) {
    UnitStats(entities_stats_, "peasant", 2, 1, 2, 1);
    RangeUnitStats(entities_stats_, "archer", 1, 2, 2, 2, 2);
    UnitStats(entities_stats_, "swordsman", 5, 1, 2, 2);
    UnitStats(entities_stats_, "cavalry", 3, 1, 4, 2);
    RangeUnitStats(entities_stats_, "catapult", 1, 4, 1, 2, 5);


    UnitStats(entities_stats_, "", 0, 0, 0, 0);
    BuildingStats(entities_stats_, "");


    EntityProductionStats(entities_factories_.units_production_stats, "peasant", 10, 1);
    CreateUnitFactory<UnitFactory>("peasant");

    EntityProductionStats(entities_factories_.units_production_stats, "swordsman", 25, 2);
    CreateUnitFactory<UnitFactory>("swordsman");

    EntityProductionStats(entities_factories_.units_production_stats, "cavalry", 25, 2);
    CreateUnitFactory<UnitFactory>("cavalry");

    EntityProductionStats(entities_factories_.units_production_stats, "archer", 25, 2);
    CreateUnitFactory<RangeUnitFactory<RangeUnit>>("archer");

    EntityProductionStats(entities_factories_.units_production_stats, "catapult", 30, 3);
    CreateUnitFactory<RangeUnitFactory<Catapult>>("catapult");
    

    EntityProductionStats(entities_factories_.buildings_production_stats, "suburb", 1, 0);
    CreateBuildingFactory<SuburbFactory>("suburb");

    EntityProductionStats(entities_factories_.buildings_production_stats, "barrack", 25, 3);
    CreateBuildingFactory<SuburbBuildingFactory<BuildingUnderConstruction<Barrack>>>("barrack");

    EntityProductionStats(entities_factories_.buildings_production_stats, "farm", 24, 2);
    CreateBuildingFactory<SuburbBuildingFactory<BuildingUnderConstruction<SuburbBuilding>>>("farm");


    SuburbBuildingStats(entities_stats_, "barrack", -2);
    SuburbBuildingStats(entities_stats_, "farm", 4);

    EntityProductionStats(entities_factories_.buildings_production_stats, "wall", 4, 4);
    CreateBuildingFactory<OutsideBuildingFactory<BuildingUnderConstruction<Wall>>>("wall");

    EntityProductionStats(entities_factories_.buildings_production_stats, "tower", 28, 3);
    CreateBuildingFactory<OutsideBuildingFactory<BuildingUnderConstruction<Tower>>>("tower");

    BuildingWithHpStats(entities_stats_, "wall", 6);
    BuildingWithHpStats(entities_stats_, "tower", 7);

    TownStats(entities_stats_, "town", 10, 4);
}

const PlayersEntitiesStats& Player::get_stats() const {
    return entities_stats_;
}

void Player::AddUnit(Unit* new_unit) {
    if (!new_unit->is_empty()) {
        unique_insert(units_, new_unit);
    }
}

void Player::NextTurn(SceneInfo& scene) {
    // it is important that get_income is called before NextTurn because it can create new buildings.
    gold_ += get_income();
    // some elements can be deleted in cycle
    auto units_copy = units_;
    for (auto unit : units_copy) {
        unit->NextTurn(scene);
    }
    auto buildings_copy = buildings_;
    for (auto building : buildings_copy) {
        building->NextTurn(scene);
    }

    if (gold_ < 0) {
        for (auto unit : units_copy) {
            unit->Kill(scene.grid);
        }
        gold_ = 0;
    }

    deleted_units_.clear();
    deleted_buildings_.clear();
}

const PlayersEntitiesFactories& Player::get_factories_stats() const {
    return entities_factories_;
}

int Player::get_gold() const {
    return gold_;
}

void Player::AddBuilding(Building* building) {
    if (building->is_empty()) {
        return;
    }
    unique_insert(buildings_, building);
    Town* town = dynamic_cast<Town*>(building);
    if (town) {
        AddTown(town);
    }
}

Color Player::get_color() const {
    return color_;
}

void Player::DeleteBuilding(std::unique_ptr<Building>&& building) {
    guaranteed_erase(buildings_, building.get());

    Town* town = dynamic_cast<Town*>(building.get());
    if (town) {
        DeleteTown(town);
    }
    deleted_buildings_.push_back(std::move(building));
}

void Player::DeleteUnit(std::unique_ptr<Unit>&& unit) {
    guaranteed_erase(units_, unit.get());

    deleted_units_.push_back(std::move(unit));
}

std::unique_ptr<Unit> Player::get_last_deleted_unit() {
    assert(!deleted_units_.empty());
    auto result = std::move(deleted_units_.back());
    deleted_units_.pop_back();
    return result;
}

std::unique_ptr<Building> Player::get_last_deleted_building() {
    assert(!deleted_buildings_.empty());
    auto result = std::move(deleted_buildings_.back());
    deleted_buildings_.pop_back();
    return result;
}

void Player::IncreaseGold(int gold_change) {
    gold_ += gold_change;
}

Town &Player::FindTown(std::pair<int, int> suburb_coord) {
    for (auto town : towns_) {
        if (town->contains_suburb(suburb_coord)) {
            return *town;
        }
    }
    assert(false);
}

int Player::get_income() const {
    int result = 0;

    for (auto building : buildings_) {
        auto suburb_building = dynamic_cast<SuburbBuilding*>(building);
        if (suburb_building) {
            result += suburb_building->get_income();
        }
    }

    for (auto unit : units_) {
        result -= unit->get_salary();
    }
    return result;
}
