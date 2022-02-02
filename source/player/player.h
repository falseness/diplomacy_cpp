#include <vector>
#include <map>
#include <source/utility/color.h>
#include <source/player/entity_stats.h>
#include <memory>
#include <source/player/entity_factories.h>
#include <list>

#pragma once

class Unit;
class Building;

struct PlayersEntitiesStats {
    std::map<std::string, EntityStats> entities;
    std::map<std::string, UnitStats> units;
    std::map<std::string, BuildingStats> buildings;
    std::map<std::string, BuildingWithHpStats> buildings_with_hp;
    std::map<std::string, SuburbBuildingStats> suburb_buildings;
    std::map<std::string, TownStats> towns;
};

struct PlayersEntitiesFactories {
    std::map<std::string, std::unique_ptr<UnitFactory>> units_factory;
    std::map<std::string, UnitProductionStats> units_production_stats;
};

class Player {
    PlayersEntitiesStats entities_stats_;
    PlayersEntitiesFactories entities_factories_;
    std::list<Unit*> units_;
    std::list<Building*> buildings_;
    template <typename Factory>
    void CreateUnitFactory(std::string name) {
        auto ptr = std::make_unique<Factory>(entities_factories_, std::move(name));
        entities_factories_.units_factory.template emplace(
                name, std::move(static_cast<std::unique_ptr<UnitFactory>>(std::move(ptr))));
    }
    int gold_ = 0;
public:
    void NextTurn();
    void AddUnit(Unit*);
    void DeleteUnit(Unit*);
    void AddBuilding(Building*);
    void DeleteBuilding(Building*);
    const Color color_;
    explicit Player(const Color&);
    [[nodiscard]] int get_gold() const;
    [[nodiscard]] Color get_color() const;
    [[nodiscard]] const PlayersEntitiesStats& get_stats() const;
    [[nodiscard]] const PlayersEntitiesFactories& get_factories_stats() const;
};

