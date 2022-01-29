#include "unit.h"
#include "source/drawable_objects/cell/coord_converter.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/unit/unit_logic.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>

const UnitStats& Unit::get_unit_type_stats() const {
    return cell_->get_player().get_stats(image_name_);
}

Unit::Unit(const Cell* cell, std::string&& image_name) : Entity(cell, std::move(image_name)) {
    const UnitStats& unit_type_stats = get_unit_type_stats();
    hp_ = unit_type_stats.hp;
    dmg_ = unit_type_stats.dmg;
    moves_ = unit_type_stats.speed;
}

void Unit::set_cell(const Cell* cell) {
    if (!cell->IsStore(this))
        throw std::invalid_argument("cell doesn't store this unit");
    cell_ = cell;
}

bool Unit::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    bool should_remove_selection = UnitLogic::ClickLogic(*this, scene.grid, coord);
    if (should_remove_selection)
        scene.entity_interface.set_visible(false);
    return should_remove_selection;
}

unsigned int Unit::get_moves() const {
    return moves_;
}

void Unit::Select(SceneInfo& scene) {
    UnitLogic::Select(*this, scene.grid);
    scene.entity_interface.update(get_info());
    scene.entity_interface.set_visible(true);
}


void Unit::MoveTo(Grid& grid, std::pair<int, int> coord) {
    moves_ -= grid.logic_helper_.get_info(coord);
    grid.MoveUnit(get_coord(), coord);
}

json Unit::to_json() {
    auto result = Entity::to_json();
    result["moves"] = moves_;
    return std::move(result);
}

json Unit::get_info() {
    auto result = Entity::get_info();
    result["info"]["hp"] = std::to_string(hp_) + " / " + std::to_string(get_maximum_hp());
    result["info"]["dmg"] = dmg_;
    result["info"]["moves"] = std::to_string(moves_) + " / " + std::to_string(get_speed());
    return std::move(result);
}

unsigned int Unit::get_speed() const {
    return get_unit_type_stats().speed;
}

unsigned int Unit::get_maximum_hp() const {
    return get_unit_type_stats().hp;
}
