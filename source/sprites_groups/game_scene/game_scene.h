#include <source/sprites_groups/scene.h>
#include <source/sprites_groups/game_scene/grid.h>

#ifndef DIPLOMACY_CPP_GAME_SCENE_H
#define DIPLOMACY_CPP_GAME_SCENE_H

class GameScene : public Scene {
    Grid *grid_;
public:
    GameScene();
    ~GameScene();
};

#endif //DIPLOMACY_CPP_GAME_SCENE_H
