#include "cell.h"
#include "coord_translation.h"
#include <source/utility/point.h>

Cell::Cell(std::pair<int, int> coord, size_t player_index_, const std::vector<Player>& players) : coord_(coord),
    player_index_(player_index_), players_(players), hexagon_(*this) {}

std::pair<int, int> Cell::get_coord() const {
    return coord_;
}

void Cell::Draw(Screen& screen, const GameOptions& game_options) {
    hexagon_.Draw(screen, game_options);
}

Point Cell::calculate_pos(const GameOptions& game_options) const {
    std::pair<float, float> transition_coord = bias_to_transition(coord_.first, coord_.second);
    return Point(transition_coord.first * game_options.hexagon_offset.x,
                 transition_coord.second * game_options.hexagon_offset.y);
}

const Color& Cell::get_color() const {
    return players_[player_index_].color_;
}