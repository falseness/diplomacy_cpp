#include <iostream>
#include <source/game.h>
#include <source/sfml_facades/screen.h>
#include <source/sfml_facades/event_manager.h>
#include <source/sprites_groups/game_scene/game_scene.h>
#include <source/options/options.h>

Game::Game() {
    game_options_ = GameOptions();

    sf::RenderWindow* window = new sf::RenderWindow();
    screen_ = new Screen(window);
    event_manager_ = new EventManager(window);
    game_scene_ = new GameScene(game_options_);
}

Game::~Game() {
    delete event_manager_;
    delete screen_;
}

void Game::MainLoop() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (screen_->IsOpen()) {
        if (event_manager_->HasCloseEvent())
            screen_->Close();
        screen_->Clear();
        //screen_->Draw(shape);
        game_scene_->Draw(*screen_, game_options_);
        screen_->Display();
    }
}