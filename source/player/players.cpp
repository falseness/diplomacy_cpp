#include "players.h"

Players::Players(std::vector<Player>&& players, size_t whoose_turn = 1) : players_(std::move(players)),
    whoose_turn_(whoose_turn){}

Player& Players::operator[](size_t index) {
    return players_[index];
}
