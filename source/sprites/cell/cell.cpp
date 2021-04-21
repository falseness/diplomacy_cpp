#include "cell.h"
#include "coord_translation.h"
#include <source/utility/point.h>

Cell::Cell(std::pair<int, int> coord, const GameOptions& game_options) : coord_(coord), hexagon_(*this) {}

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
