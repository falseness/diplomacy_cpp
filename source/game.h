#include <source/sfml_facades/library_facade.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>

#pragma once

class Game {
    LibraryFacade library_facade_;
    GameScene* game_scene_;
    GameOptions game_options_;
    void EventsIteration();
    void DrawingIteration();
public:
    Game();
    void MainLoop();
};
