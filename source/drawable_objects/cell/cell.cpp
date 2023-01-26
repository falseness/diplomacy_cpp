#include "cell.h"
#include "source/drawable_objects/cell/coord_converter.h"
#include "source/utility/vector2d.h"
#include "source/player/players.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"


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

void Cell::MoveUnitTo(const Cell& destination, Grid &grid) const {
    assert(destination.get_unit()->is_empty());
    if (!destination.is_my_turn() && destination.is_suburb()) {
        grid.DeleteSuburb(destination.get_coord());
    }

    grid.MoveUnit(get_coord(), destination.get_coord());
    grid.SetPlayer(destination.get_coord(), player_index_);
}

void Cell::MoveUnitTo(Cell &destination) {
    destination.set_unit(std::move(unit_));
    unit_ = std::make_unique<EmptyUnit>(this);
}

void Cell::set_player(size_t player_index) {
    player_index_ = player_index;
}

const float Cell::kColorAlphaRatio = 0.4f;

bool Cell::is_my_turn() const {
    return is_my_player(players_.get_whoose_turn());
}

bool Cell::is_passable() const {
    return building_->is_passable() && unit_->is_passable();
}

bool Cell::is_hittable(size_t another_player_index) const {
    return building_->is_hittable(another_player_index) || unit_->is_hittable(another_player_index);
}

void Cell::DeleteUnit() {
    if (!unit_->is_empty()) {
        get_player().DeleteUnit(std::move(unit_));
        unit_ = std::make_unique<EmptyUnit>(this);
    }
}

void Cell::DeleteBuilding() {
    if (!building_->is_empty()) {
        get_player().DeleteBuilding(std::move(building_));
        building_ = std::make_unique<EmptyBuilding>(this);
    }
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
    if (get_building()->is_hittable(players_.get_whoose_turn())) {
        auto building = dynamic_cast<const HittableEntity*>(get_building());
        building->Hit(dmg, grid);
        return;
    }
    if (get_unit()->is_hittable(players_.get_whoose_turn())) {
        get_unit()->Hit(dmg, grid);
        return;
    }
    assert(false);
}

//unsafe function. refactoring is needed
void Cell::SetUnit(std::unique_ptr<Unit>&& unit) {
    assert(unit_->is_empty());
    assert(unit->get_cell() == this);
    get_player().AddUnit(unit.get());
    unit_ = std::move(unit);
}

void Cell::SetBuilding(std::unique_ptr<Building> &&building) {
    assert(building_->is_empty());
    assert(building->get_cell() == this);
    get_player().AddBuilding(building.get());
    building_ = std::move(building);
}

bool Cell::is_my_player(size_t another_player_index) const {
    return another_player_index == player_index_;
}
