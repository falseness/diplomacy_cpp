#include "source/player/factories/entity.h"
#include "source/drawable_objects/entity.h"

#pragma once

class SceneInfo;
class Town;

class BuildingFactory : public EntityFactory {
public:
    [[nodiscard]] unsigned int get_turns_left(const Player&, const ProductionInfo&) const override;
    BuildingFactory(PlayersEntitiesFactories& all_factories, std::string);
    virtual void Select(SceneInfo&, const Town*) = 0;
    virtual ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&, Town* town) = 0;
};

class SuburbFactory : public BuildingFactory {
    static const int kArithmeticProgressionDelta = 2;
    static const int kBaseCost = 1;
public:
    void Select(SceneInfo&, const Town*) override;
    SuburbFactory(PlayersEntitiesFactories& all_factories, std::string);
    ClickResponse HandleClick(SceneInfo& scene, const Vector2D& click_pos, const GameOptions& game_option,
                              Town* town) override;
};
