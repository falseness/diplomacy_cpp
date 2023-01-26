#include <vector>
#include <map>
#include <deque>
#include "source/utility/color.h"
#include "source/player/entity_stats.h"
#include "source/player/factories/entity.h"
#include "source/player/factories/building_and_suburb.h"
#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/building/building.h"

#include <list>
#include <memory>


#pragma once

class Unit;
class Building;
class BuildingAndSuburbFactory;

struct PlayersEntitiesStats {
    std::map<std::string, EntityStats> entities;
    std::map<std::string, UnitStats> units;
    std::map<std::string, RangeUnitStats> range_units;
    std::map<std::string, BuildingStats> buildings;
    std::map<std::string, BuildingWithHpStats> buildings_with_hp;
    std::map<std::string, SuburbBuildingStats> suburb_buildings;
    std::map<std::string, TownStats> towns;
};

struct PlayersEntitiesFactories {
    std::map<std::string, std::unique_ptr<UnitFactory>> units_factory;
    std::map<std::string, std::unique_ptr<BuildingAndSuburbFactory>> buildings_factory;
    std::map<std::string, EntityProductionStats> units_production_stats;
    std::map<std::string, EntityProductionStats> buildings_production_stats;
};

class Player {
    PlayersEntitiesStats entities_stats_;
    PlayersEntitiesFactories entities_factories_;
    std::list<Unit*> units_;
    std::list<Building*> buildings_;
    std::unique_ptr<Unit> tmp_;
    std::deque<std::unique_ptr<Unit>> deleted_units_;
    std::deque<std::unique_ptr<Building>> deleted_buildings_;
    template <typename Factory>
    void CreateUnitFactory(std::string name) {
        auto ptr = std::make_unique<Factory>(entities_factories_, name);
        entities_factories_.units_factory.template emplace(
                std::move(name), std::move(static_cast<std::unique_ptr<UnitFactory>>(std::move(ptr))));
    }
    template <typename Factory>
    void CreateBuildingFactory(std::string name) {
        auto ptr = std::make_unique<Factory>(entities_factories_, name);
        entities_factories_.buildings_factory.template emplace(
                std::move(name), std::move(std::unique_ptr<BuildingAndSuburbFactory>(std::move(ptr))));
    }
    int gold_ = 0;
public:
    void NextTurn(SceneInfo& scene);
    void AddUnit(Unit*);
    void DeleteUnit(std::unique_ptr<Unit>&& unit);
    void AddBuilding(Building*);
    void DeleteBuilding(std::unique_ptr<Building>&& building);
    std::unique_ptr<Unit> get_last_deleted_unit();
    std::unique_ptr<Building> get_last_deleted_building();
    const Color color_;
    explicit Player(const Color&);
    [[nodiscard]] int get_gold() const;
    [[nodiscard]] Color get_color() const;
    [[nodiscard]] const PlayersEntitiesStats& get_stats() const;
    [[nodiscard]] const PlayersEntitiesFactories& get_factories_stats() const;
};

