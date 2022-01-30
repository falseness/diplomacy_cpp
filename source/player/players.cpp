#include "players.h"
#include <cassert>

Players::Players(std::vector<Player>&& players, size_t whoose_turn = 1) : players_(std::move(players)),
    whoose_turn_(whoose_turn){}

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
