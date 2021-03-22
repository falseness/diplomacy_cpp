#include <SFML/Graphics.hpp>
#include <vector>

class EventManager {
    sf::RenderWindow* window_;
    std::vector<sf::Event> get_events() {
        std::vector<sf::Event> events;
        sf::Event event;
        while (window_->pollEvent(event)) {
            events.push_back(event);
        }
        return events;
    }
public:
    EventManager(sf::RenderWindow* window) : window_(window) {} 
    bool HasCloseEvent() {
        std::vector<sf::Event> events = get_events();
        for (auto event : events) {
            if (event.type == sf::Event::Closed)
                return true;
        }
        return false;
    }
};
