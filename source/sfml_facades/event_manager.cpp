#include <SFML/Graphics.hpp>
#include "event_manager.h"
#include <vector>

const std::pair<Vector2D, bool> EventManager::no_click_event_ = std::make_pair(Vector2D(0, 0), false);

void EventManager::HandleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            has_close_event_ = true;
        else if (event.type == sf::Event::MouseButtonPressed)
            click_event_ = std::make_pair(Vector2D(static_cast<float>(event.mouseButton.x),
                                                   static_cast<float>(event.mouseButton.y)), true);
    }
}

EventManager::EventManager(sf::RenderWindow& window) : window_(window),
    click_event_(no_click_event_) {}

void EventManager::NextIteration() {
    click_event_ = no_click_event_;
    has_close_event_ = false;
    HandleEvents();
}

bool EventManager::HasCloseEvent() {
    return has_close_event_;
}

const std::pair<Vector2D, bool>& EventManager::get_click_event() {
    return click_event_;
}