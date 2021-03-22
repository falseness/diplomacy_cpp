#include <iostream>
#include <SFML/Window.hpp>
#include <source/sfml_facades/screen.cpp>
#include <source/sfml_facades/event_manager.cpp>


class Game {
    Screen* screen;
    EventManager* event_manager;
public:
    Game() {
        sf::RenderWindow* window = new sf::RenderWindow();
        screen = new Screen(window);
        event_manager = new EventManager(window);
    }
    ~Game() {
        delete event_manager;
        delete screen;
    }
    void MainLoop() {
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        while (screen->IsOpen()) {
            if (event_manager->HasCloseEvent()) 
                screen->Close();
            screen->Clear();
            screen->Draw(shape);
            screen->Display();
        }
    }
};
