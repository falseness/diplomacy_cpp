#pragma once

#include "source/player/player.h"

// non-human player on 0 index of players array
class Player0 : public Player {
    const size_t kPlayerIndex = 0;
    void DeleteOtherAndSpawnSea(std::pair<int, int> coord, Grid &grid);
public:
    using Player::Player;
    void NextTurn(SceneInfo& scene) override;
};
