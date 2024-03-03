#include "source/sfml_facades/library_facade.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"


#include "source/utility/fps_counter.h"


#pragma once

class Game {
    LibraryFacade library_facade_;
    std::unique_ptr<GameScene> game_scene_;
    GameOptions game_options_;
    FramesCounter frames_counter_;
    void ScaleCamera(const MouseWheelInfo&);
    void EventsIteration();
    void DrawingIteration();
public:
    Game();
    void MainLoop();
};
