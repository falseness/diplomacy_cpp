#include "range_unit.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/unit/range/range_unit_logic.h"
#include "source/drawable_objects/unit/range/catapult_logic.h"


RangeUnit::RangeUnit(Cell* cell, std::string name) : Unit(cell, name), Entity(cell, std::move(name)) {

}

unsigned int RangeUnit::get_unit_base_range() const {
    auto it = get_player_stats().range_units.find(image_name_);
    assert(it != get_player_stats().range_units.end());
    return static_cast<unsigned int>(it->second.range);
}

unsigned int RangeUnit::get_range() const {
    int result = static_cast<int>(get_unit_base_range()) + get_cell()->get_building()->get_range_addition();
    result = std::max(0, result);
    return static_cast<unsigned int>(result);
}

void RangeUnit::AttackSomething(Grid &grid, std::pair<int, int> cell_coord) const {
    const Cell& cell = *grid.get_cell(cell_coord);
    assert(is_attackable(cell));
    grid.DecreaseUnitMoves(get_coord(), static_cast<int>(get_moves()));

    AttackAfterPreparations(grid, cell_coord, cell);
}

void RangeUnit::AttackAfterPreparations(Grid &grid, std::pair<int, int> &cell_coord, const Cell &cell) const {
    if (cell.is_hittable(get_player_index())) {
        cell.HitSomethingOnCell(dmg_, grid);
    }
    else {
        grid.DeleteBuilding(cell_coord);
    }
}

void RangeUnit::Select(const SceneInfo & scene) const {
    scene.range_unit_attack_border.set_inner_line_color(get_color());

    unsigned int bfs_moves = (is_my_turn() && !get_moves()) ? 0 : get_range();
    CallUnitLogicSelect(scene, bfs_moves);
    Unit::Select(scene);
}

void RangeUnit::CallUnitLogicSelect(const SceneInfo &scene,
                                    unsigned int bfs_moves) const {
    // todo: refactor it
    if (is_on_high_ground()) {
        CatapultUnitLogic::kCatapultUnitLogic.Select(scene, *this, bfs_moves);
    }
    else {
        RangeUnitLogic::kRangeUnitLogic.Select(scene, *this, bfs_moves);
    }
}

ClickResponse RangeUnit::ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const {
    if (is_on_high_ground()) {
        return CatapultUnitLogic::kCatapultUnitLogic.ClickLogic(*this, scene.grid, coord);
    }
    return RangeUnitLogic::kRangeUnitLogic.ClickLogic(*this, scene.grid, coord);
}

ClickResponse RangeUnit::HandleClick(SceneInfo &scene, const Vector2D &click_pos,
                                     const GameOptions &game_options) const {
    scene.range_unit_attack_border.Clear();
    return Unit::HandleClick(scene, click_pos, game_options);
}

json RangeUnit::get_info() const {
    auto result = Unit::get_info();
    result["info"]["range"] = get_range();
    return result;
}
