#include <iostream>
#include <SFML/Window.hpp>
#include <source/game.h>
#include <source/sfml_facades/screen.h>
#include <source/sfml_facades/event_manager.h>
#include <source/sprites_groups/game_scene/game_scene.h>

Game::Game() {
    sf::RenderWindow* window = new sf::RenderWindow();
    screen = new Screen(window);
    event_manager = new EventManager(window);
    game_scene = new GameScene();
}

Game::~Game() {
    delete event_manager;
    delete screen;
}

void Game::MainLoop() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (screen->IsOpen()) {
        if (event_manager->HasCloseEvent())
            screen->Close();
        screen->Clear();
        //screen->Draw(shape);
        game_scene->Draw(*screen);
        screen->Display();
    }
}