#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/sfml_facades/screen.h>
#include <source/sfml_facades/event_manager.h>

#pragma once

struct LibraryFacade {
private:
    sf::RenderWindow window;
public:
    Screen screen;
    EventManager event_manager;
    LibraryFacade();
};