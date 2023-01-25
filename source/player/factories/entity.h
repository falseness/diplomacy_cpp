#pragma once

#include <memory>
#include <map>

class Unit;
class Player;

class Cell;

class PlayersEntitiesFactories;

struct ProductionInfo {
    std::string name;
    unsigned int turns;
};

struct EntityProductionStats {
    int cost;
    unsigned int turns;
    EntityProductionStats(std::map<std::string, EntityProductionStats>& stats, std::string, int, unsigned int);
};

class EntityFactory {
public:
    [[nodiscard]] virtual unsigned int get_turns_left(const Player&, const ProductionInfo&) const = 0;
    void NextTurn(const Player&, ProductionInfo&) const;
    virtual ~EntityFactory() = default;
};

class UnitFactory : public EntityFactory {
public:
    [[nodiscard]] unsigned int get_turns_left(const Player&, const ProductionInfo&) const override;
    virtual void Create(Cell*, const ProductionInfo& production) const;
    UnitFactory(PlayersEntitiesFactories& all_factories, std::string);
};
