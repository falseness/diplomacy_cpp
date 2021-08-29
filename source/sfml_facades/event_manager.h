#include <source/utility/vector2d.h>

#pragma once

class EventManager {
    sf::RenderWindow& window_;
    void HandleEvents();
    bool has_close_event_;
    std::pair<Vector2D, bool> click_event_;
    static const std::pair<Vector2D, bool> no_click_event_;
public:
    void NextIteration();
    EventManager(sf::RenderWindow& window);
    bool HasCloseEvent();
    const std::pair<Vector2D, bool>& get_click_event();
};
