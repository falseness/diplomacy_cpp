#include "players.h"
#include <cassert>


Players::Players(std::vector<Color>&& players_colors, size_t whoose_turn = 1) : whoose_turn_(whoose_turn) {
        for (auto&& color : players_colors) {
            players_.emplace_back(color);
        }
}

Player& Players::operator[](size_t index) {
    return players_[index];
}

void Players::NextTurn() {
    assert(players_.size() > 1);
    whoose_turn_ = (whoose_turn_ + 1) % players_.size();
    players_[whoose_turn_].NextTurn();
    if (!whoose_turn_)
        NextTurn();
}

size_t Players::get_whoose_turn() const {
    return whoose_turn_;
}


