#include <deque>
#include "source/player/factories/entity.h"
#include "source/drawable_objects/entity.h"
#include "source/drawable_objects/cell/coord_converter.h"

class Town;
class SceneInfo;
class Grid;

#pragma once

class BuildingFactory : public EntityFactory {
protected:
    virtual void BFSBody(
            std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
            std::deque<std::pair<int, int>>& coords, int distance,
            const std::pair<int, int>& neighbour) const = 0;
    static bool is_correct_click(SceneInfo &scene, std::pair<int, int> coord);
public:
    [[nodiscard]] unsigned int get_turns_left(const Player&, const ProductionInfo&) const override;
    BuildingFactory(PlayersEntitiesFactories& all_factories, std::string);
    virtual void Select(SceneInfo&, const Town*);
    virtual ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&, Town* town) = 0;
};

class SuburbFactory : public BuildingFactory {
    static const int kArithmeticProgressionDelta = 2;
    static const int kBaseCost = 1;
    void BFSBody(
            std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
            std::deque<std::pair<int, int>>& coords, int distance,
            const std::pair<int, int>& neighbour) const override;
public:
    SuburbFactory(PlayersEntitiesFactories& all_factories, std::string);
    ClickResponse HandleClick(SceneInfo& scene, const Vector2D& click_pos, const GameOptions& game_option,
                              Town* town) override;
};