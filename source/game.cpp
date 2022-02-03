#include <iostream>
#include "game.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include "source/options/game.h"

Game::Game() {
    game_options_ = GameOptions();

    game_scene_ = std::make_unique<GameScene>(library_facade_.screen, game_options_);
    library_facade_.screen.set_draw_offset(Vector2D(100.f, 100.f));
}

void Game::EventsIteration() {
    library_facade_.event_manager.NextIteration();

    if (library_facade_.event_manager.HasCloseEvent()) {
        library_facade_.screen.Close();
        return;
    }
    const std::pair<Vector2D, bool>& click_event = library_facade_.event_manager.get_click_event();
    if (click_event.second) {
        game_options_.draw_offset = library_facade_.screen.get_draw_offset();
        game_scene_->HandleClick(click_event.first, game_options_);
    }
}

void Game::DrawingIteration() {
    library_facade_.screen.Clear();
    game_scene_->Draw(library_facade_.screen, game_options_);
    library_facade_.screen.Display();
}

void Game::MainLoop() {
    while (library_facade_.screen.IsOpen()) {
        EventsIteration();
        DrawingIteration();
    }
}
