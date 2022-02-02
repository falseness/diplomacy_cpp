#include <memory>

#pragma once

class Unit;
class Player;
class PlayersEntitiesFactories;
class Cell;

struct ProductionInfo {
    std::string unit_name;
    unsigned int turns;
};

struct UnitProductionStats {
    int cost;
    unsigned int turns;
    UnitProductionStats(PlayersEntitiesFactories&, std::string, int, unsigned int);
};

class UnitFactory {
public:
    [[nodiscard]] virtual unsigned int get_turns_left(const Player&, const ProductionInfo&) const;
    void NextTurn(const Player&, ProductionInfo&) const;
    explicit UnitFactory(PlayersEntitiesFactories& all_factories, std::string&&);
    virtual void CreateUnit(Cell*, const ProductionInfo& production) const;
    virtual ~UnitFactory() = default;
};
