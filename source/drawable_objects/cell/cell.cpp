#include "cell.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/utility/vector2d.h>
#include <iostream>

Cell::Cell(std::pair<int, int> coord, size_t player_index_, const std::vector<Player>& players) :
    coord_(std::move(coord)), player_index_(player_index_), players_(players), hexagon_(*this), unit_(nullptr) {}

std::pair<int, int> Cell::get_coord() const {
    return coord_;
}

void Cell::Draw(Screen& screen, const GameOptions& game_options) {
    hexagon_.Draw(screen, game_options);
    if (building_ != nullptr)
        building_->Draw(screen, game_options);
    if (unit_ != nullptr)
        unit_->Draw(screen, game_options);

}

Vector2D Cell::get_pos(const GameOptions& game_options) const {
    std::pair<float, float> transition_coord = CoordConverter::BiasToTransition(coord_.first, coord_.second);
    return Vector2D(transition_coord.first * game_options.hexagon_offset.x,
                 transition_coord.second * game_options.hexagon_offset.y);
}

const Color& Cell::get_color() const {
    return players_[player_index_].color_;
}

const Player& Cell::get_player() const {
    return players_[player_index_];
}

bool Cell::IsStore(const Unit* unit) const {
    return unit == unit_.get();
}

Unit* Cell::get_unit() {
    return unit_.get();
}

void Cell::set_unit(std::unique_ptr<Unit>&& new_unit) {
    unit_ = std::move(new_unit);
    unit_->set_cell(this);
}

void Cell::MoveUnitTo(Cell& cell) {
    if (cell.unit_ != nullptr)
        throw std::invalid_argument("cell unit is not nullptr");
    cell.set_unit(std::move(unit_));
}

Building* Cell::get_building() {
    return building_.get();
}
