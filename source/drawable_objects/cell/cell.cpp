#include "cell.h"
#include <source/drawable_objects/cell/coord_converter.h>
#include <source/utility/vector2d.h>
#include <source/player/players.h>


Cell::Cell(std::pair<int, int> coord, size_t player_index_, Players& players, bool is_suburb) :
    coord_(std::move(coord)), player_index_(player_index_), players_(players), hexagon_(*this),
    unit_(std::move(std::make_unique<EmptyUnit>(this))), building_(std::move(std::make_unique<EmptyBuilding>(this))),
    is_suburb_(is_suburb){}

std::pair<int, int> Cell::get_coord() const {
    return coord_;
}

void Cell::Draw(Screen& screen, const GameOptions& game_options) {
    hexagon_.Draw(screen, game_options);
    if (!building_->is_empty())
        building_->Draw(screen, game_options);
    if (!unit_->is_empty())
        unit_->Draw(screen, game_options);

}

Vector2D Cell::get_pos(const GameOptions& game_options) const {
    std::pair<float, float> transition_coord = CoordConverter::BiasToTransition(coord_.first, coord_.second);
    return {transition_coord.first * game_options.hexagon_offset.x,
                 transition_coord.second * game_options.hexagon_offset.y};
}

const Color& Cell::get_color() const {
    return get_player().color_;
}

Player& Cell::get_player() {
    return players_[player_index_];
}
const Player& Cell::get_player() const {
    return players_[player_index_];
}

bool Cell::IsStore(const Unit* unit) const {
    return unit == unit_.get();
}

void Cell::set_unit(std::unique_ptr<Unit>&& new_unit) {
    unit_ = std::move(new_unit);
    unit_->set_cell(this);
}

void Cell::MoveUnitTo(Cell& cell) {
    assert(cell.unit_->is_empty());
    if (!cell.is_my_turn() && cell.is_suburb())
        cell.is_suburb_ = false;
    cell.set_unit(std::move(unit_));
    cell.set_player(player_index_);

    unit_ = std::make_unique<EmptyUnit>(this);
}

void Cell::set_player(size_t player_index) {
    player_index_ = player_index;
}

const float Cell::kColorAlphaRatio = 0.4f;

bool Cell::is_my_turn() const {
    return player_index_ == players_.get_whoose_turn();
}

bool Cell::is_passable() const {
    return building_->is_passable() && unit_->is_passable();
}

bool Cell::is_hittable() const {
    return building_->is_hittable() || unit_->is_hittable();
}

void Cell::DeleteUnit() {
    get_player().DeleteUnit(unit_.get());
    unit_ = std::make_unique<EmptyUnit>(this);
}

void Cell::DeleteBuilding() {
    building_ = std::make_unique<EmptyBuilding>(this);
}

bool Cell::is_suburb() const {
    return is_suburb_;
}

Segment Cell::get_side(uint8_t side_index, Screen& screen, const GameOptions& game_options) const {
    return hexagon_.get_side(side_index, screen, game_options);
}

void Cell::set_suburb(bool suburb_state) {
    is_suburb_ = suburb_state;
}

void Cell::HitSomethingOnCell(int dmg, Grid& grid) const {
    if (get_building()->is_hittable()) {
        auto building = dynamic_cast<const HittableEntity*>(get_building());
        building->Hit(dmg, grid);
        return;
    }
    if (get_unit()->is_hittable()) {
        get_unit()->Hit(dmg, grid);
        return;
    }
    assert(false);
}

