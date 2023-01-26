#include "range_unit.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/unit/range/range_unit_logic.h"


RangeUnit::RangeUnit(Cell* cell, std::string name) : Unit(cell, name), Entity(cell, std::move(name)) {

}

unsigned int RangeUnit::get_range() const {
    auto it = get_player_stats().range_units.find(image_name_);
    assert(it != get_player_stats().range_units.end());
    int result = static_cast<int>(it->second.range) + get_cell()->get_building()->get_range_addition();
    result = std::max(0, result);
    return static_cast<unsigned int>(result);
}

void RangeUnit::AttackSomething(Grid &grid, std::pair<int, int> cell_coord) const {
    const Cell& cell = *grid.get_cell(cell_coord);
    assert(is_attackable(cell));
    grid.DecreaseUnitMoves(get_coord(), static_cast<int>(get_moves()));

    if (cell.is_hittable()) {
        cell.HitSomethingOnCell(dmg_, grid);
    }
    else {
        grid.DeleteBuilding(cell_coord);
    }
}

void RangeUnit::Select(const SceneInfo & scene) const {
    scene.range_unit_attack_border.set_inner_line_color(get_color());

    unsigned int bfs_moves = (is_my_turn() && !get_moves()) ? 0 : get_range();
    RangeUnitLogic::kRangeUnitLogic.Select(scene, *this, bfs_moves);
    Unit::Select(scene);
}

ClickResponse RangeUnit::ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const {
    ClickResponse click_response = RangeUnitLogic::kRangeUnitLogic.ClickLogic(*this, scene.grid, coord);
    return click_response;
}

ClickResponse RangeUnit::HandleClick(SceneInfo &scene, const Vector2D &click_pos,
                                     const GameOptions &game_options) const {
    scene.range_unit_attack_border.Clear();
    return Unit::HandleClick(scene, click_pos, game_options);
}
