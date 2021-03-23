#ifndef DIPLOMACY_CPP_EVENT_MANAGER_H
#define DIPLOMACY_CPP_EVENT_MANAGER_H

class EventManager {
    sf::RenderWindow* window_;
    std::vector<sf::Event> get_events();
public:
    EventManager(sf::RenderWindow* window);
    bool HasCloseEvent();
};

#endif //DIPLOMACY_CPP_EVENT_MANAGER_H
