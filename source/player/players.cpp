#include "players.h"
#include <cassert>


Players::Players(std::vector<Color>&& players_colors, size_t whoose_turn = 1) : whoose_turn_(whoose_turn) {
        for (auto&& color : players_colors) {
            players_.emplace_back(color);
        }
}

Player& Players::operator[](size_t index) {
    assert(index < players_.size());
    return players_[index];
}

void Players::NextTurn(SceneInfo &scene) {
    assert(players_.size() > 1);
    whoose_turn_ = (whoose_turn_ + 1) % players_.size();
    players_[whoose_turn_].NextTurn(scene);
    if (!whoose_turn_)
        NextTurn(scene);
}

size_t Players::get_whoose_turn() const {
    return whoose_turn_;
}

const Player &Players::operator[](size_t index) const {
    assert(index < players_.size());
    return players_[index];
}


