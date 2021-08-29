#include "unit.h"
#include <source/drawable_objects/cell/cell.h>

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