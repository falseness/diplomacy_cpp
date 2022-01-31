#include <memory>

#pragma once

class Unit;
class Player;
class PlayersEntitiesFactories;
class Cell;

struct ProductionInfo {
    unsigned int turns;
};

struct UnitProductionStats {
    int cost;
    unsigned int turns;
    UnitProductionStats(PlayersEntitiesFactories&, std::string, int, unsigned int);
};

class UnitFactory {
    std::string unit_name_;
public:
    [[nodiscard]] unsigned int get_turns_left(const Player&, const ProductionInfo&) const;
    void NextTurn(const Player&, ProductionInfo&) const;
    explicit UnitFactory(PlayersEntitiesFactories& all_factories, std::string&&);
    virtual void CreateUnit(Cell*);
    virtual ~UnitFactory() = default;
};
