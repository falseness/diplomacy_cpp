#include "unit.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/unit/unit_logic.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>

const UnitStats& Unit::get_stats() const {
    return cell_->get_player().get_stats().units.find(image_name_)->second;
}

Unit::Unit(const Cell* cell, std::string&& image_name) : Entity(cell, std::move(image_name)) {
    const UnitStats& unit_type_stats = get_stats();
    hp_ = unit_type_stats.hp;
    dmg_ = unit_type_stats.dmg;
    moves_ = unit_type_stats.speed;
}

void Unit::set_cell(const Cell* cell) {
    if (!cell->IsStore(this))
        throw std::invalid_argument("cell doesn't store this unit");
    cell_ = cell;
}

ClickResponse Unit::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    ClickResponse click_response = UnitLogic::ClickLogic(*this, scene.grid, coord);
    if (click_response.should_remove_selection)
        scene.entity_interface.set_visible(false);
    return click_response;
}

unsigned int Unit::get_moves() const {
    return moves_;
}

void Unit::Select(SceneInfo& scene) {
    UnitLogic::Select(*this, scene.grid);
    Entity::Select(scene);
}


void Unit::MoveTo(Grid& grid, std::pair<int, int> coord) {
    moves_ -= grid.logic_helper_.get_info(coord);

    std::vector<std::pair<int, int>> path;
    auto this_coord = coord;
    while (this_coord != get_coord()) {
        path.push_back(this_coord);
        this_coord = grid.logic_helper_.get_parent(this_coord);
    }
    reverse(path.begin(), path.end());
    for (auto next_coord : path) {
        grid.MoveUnit(get_coord(), next_coord);
    }

}

json Unit::to_json() {
    auto result = Entity::to_json();
    result["hp"] = hp_;
    result["moves"] = moves_;
    return std::move(result);
}

json Unit::get_info() const {
    auto result = Entity::get_info();
    result["info"]["hp"] = std::to_string(hp_) + " / " + std::to_string(get_maximum_hp());
    result["info"]["dmg"] = dmg_;
    result["info"]["moves"] = std::to_string(moves_) + " / " + std::to_string(get_speed());
    return std::move(result);
}

unsigned int Unit::get_speed() const {
    return get_stats().speed;
}

unsigned int Unit::get_maximum_hp() const {
    return get_stats().hp;
}

void Unit::NextTurn() {
    moves_ = get_speed();
}
