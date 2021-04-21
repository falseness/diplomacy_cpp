#pragma once

class EventManager {
    sf::RenderWindow& window_;
    std::vector<sf::Event> get_events();
public:
    EventManager(sf::RenderWindow& window);
    bool HasCloseEvent();
};
