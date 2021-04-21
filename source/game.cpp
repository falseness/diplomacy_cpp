#include <iostream>
#include "game.h"
#include <source/sprites_groups/game_scene/game_scene.h>
#include <source/options/options.h>

Game::Game() {
    game_options_ = GameOptions();

    game_scene_ = new GameScene(game_options_);
}

void Game::MainLoop() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (library_facade_.screen.IsOpen()) {
        if (library_facade_.event_manager.HasCloseEvent())
            library_facade_.screen.Close();
        library_facade_.screen.Clear();
        //screen_->Draw(shape);
        game_scene_->Draw(library_facade_.screen, game_options_);
        library_facade_.screen.Display();
    }
}