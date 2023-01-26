#include "catapult.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/unit/range/catapult_logic.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"

void Catapult::AttackAfterPreparations(Grid &grid, std::pair<int, int> &cell_coord, const Cell &cell) const {
    const Building& building = *cell.get_building();
    assert(!building.is_empty());
    if (building.is_hittable(get_player_index())) {
        grid.DecreaseBuildingHP(cell_coord, dmg_);
    }
    else {
        grid.DeleteBuilding(cell_coord);
    }
}

void Catapult::CallUnitLogicSelect(const SceneInfo &scene, unsigned int bfs_moves) const {
    CatapultUnitLogic::kCatapultUnitLogic.Select(scene, *this, bfs_moves);
}

ClickResponse Catapult::ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const {
    return CatapultUnitLogic::kCatapultUnitLogic.ClickLogic(*this, scene.grid, coord);
}

Catapult::Catapult(Cell* cell, std::string name) : RangeUnit(cell, name), Unit(cell, name),
    Entity(cell, std::move(name)) {
}

