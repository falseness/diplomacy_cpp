#include "players.h"

#include <cassert>

#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/player/player0.h"

Players::Players(std::vector<Color>&& players_colors, size_t whoose_turn = 1) : whoose_turn_(whoose_turn) {
    players_.push_back(std::move(std::make_unique<Player0>(players_colors[0])));
    for (size_t i = 1; i < players_colors.size(); ++i) {
        players_.push_back(std::move(std::make_unique<Player>(players_colors[i])));
    }
}

Player& Players::operator[](size_t index) {
    assert(index < players_.size());
    return *players_[index];
}

void Players::NextTurn(SceneInfo &scene) {
    assert(players_.size() > 1);
    whoose_turn_ = (whoose_turn_ + 1) % players_.size();
    players_[whoose_turn_]->NextTurn(scene);
    if (!whoose_turn_) {
        NextTurn(scene);
    }
}

size_t Players::get_whoose_turn() const {
    return whoose_turn_;
}

const Player &Players::operator[](size_t index) const {
    assert(index < players_.size());
    return *players_[index];
}


