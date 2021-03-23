#include <SFML/Window.hpp>
#include <source/sfml_facades/screen.h>
#include <source/sfml_facades/event_manager.h>
#include <source/sprites_groups/game_scene/game_scene.h>

#ifndef DIPLOMACY_CPP_GAME_H
#define DIPLOMACY_CPP_GAME_H
class Game {
    Screen* screen_;
    EventManager* event_manager_;
    GameScene* game_scene_;
    GameOptions game_options_;
public:
    Game();
    ~Game();
    void MainLoop();
};

#endif //DIPLOMACY_CPP_GAME_H
