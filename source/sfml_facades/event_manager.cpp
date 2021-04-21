#include <SFML/Graphics.hpp>
#include "event_manager.h"
#include <vector>

std::vector<sf::Event> EventManager::get_events() {
    std::vector<sf::Event> events;
    sf::Event event;
    while (window_.pollEvent(event)) {
        events.push_back(event);
    }
    return events;
}

EventManager::EventManager(sf::RenderWindow& window) : window_(window) {}

bool EventManager::HasCloseEvent() {
    std::vector<sf::Event> events = get_events();
    for (auto event : events) {
        if (event.type == sf::Event::Closed)
            return true;
    }
    return false;
}
