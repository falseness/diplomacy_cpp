#pragma once

#include "source/player/player.h"

// non-human player on 0 index of players array
class Player0 : public Player {
public:
    void NextTurn(SceneInfo& scene) override;
};
