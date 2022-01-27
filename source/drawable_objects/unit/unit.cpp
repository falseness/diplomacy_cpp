#include "unit.h"
#include "source/drawable_objects/cell/coord_converter.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <source/drawable_objects/unit/unit_logic.h>

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

bool Unit::HandleClick(Grid* grid, const Vector2D &click_pos, const GameOptions &game_options) {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    return UnitLogic::ClickLogic(this, grid, coord);
}

unsigned int Unit::get_moves() const {
    return moves_;
}

void Unit::Select(Grid* grid) {
    UnitLogic::Select(this, grid);
}
#include <iostream>
void Unit::MoveTo(Grid* grid, std::pair<int, int> coord) {
    moves_ -= grid->logic_helper_.get_info(coord);
    grid->MoveUnit(get_coord(), coord);
}
