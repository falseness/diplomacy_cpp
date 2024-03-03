#include <SFML/Graphics.hpp>
#include "event_manager.h"
#include <vector>

const std::pair<Vector2D, bool> EventManager::no_click_event_ = std::make_pair(Vector2D(0, 0), false);

void EventManager::HandleEvents() {
    static const std::map<sf::Keyboard::Key, ArrowsKeyPressInfo> get_arrow_info_change = {
                {sf::Keyboard::Left, {-1, 0}}, {sf::Keyboard::A, {-1, 0}},
                {sf::Keyboard::Right, {1, 0}}, {sf::Keyboard::D, {1, 0}},
                {sf::Keyboard::Up, {0, -1}}, {sf::Keyboard::W, {0, -1}},
                {sf::Keyboard::Down, {0, 1}}, {sf::Keyboard::S, {0, 1}}};

    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            has_close_event_ = true;
            continue;
        }
        if (event.type == sf::Event::MouseWheelMoved) {
            mouse_wheel_event_ = {.delta = event.mouseWheel.delta, .x = event.mouseWheel.x, .y = event.mouseWheel.y};
            continue;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            click_event_ = std::make_pair(Vector2D(static_cast<float>(event.mouseButton.x),
                                                   static_cast<float>(event.mouseButton.y)), true);
            continue;
        }

        if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased) {
            continue;
        }
        if (event.type == sf::Event::KeyPressed) {
            has_key_press_backspace_event_ = event.key.code == kKeyboardPressBackspaceButton;
            has_key_press_enter_event_ = event.key.code == kKeyboardPressEnterButton;
        }
        auto it = get_arrow_info_change.find(event.key.code);
        if (it == get_arrow_info_change.end()) {
            continue;
        }
        int8_t multiplier = event.type == sf::Event::KeyPressed ? 1 : -1;
        arrows_info_.hotizontal_sum += it->second.hotizontal_sum * multiplier;
        arrows_info_.vertical_sum += it->second.vertical_sum * multiplier;

    }
}

EventManager::EventManager(sf::RenderWindow& window) : window_(window),
    click_event_(no_click_event_) {
    window_.sf::Window::setKeyRepeatEnabled(false);
}

void EventManager::NextIteration() {
    click_event_ = no_click_event_;
    has_close_event_ = false;
    has_key_press_backspace_event_ = has_key_press_enter_event_ = false;
    mouse_wheel_event_ = std::nullopt;
    HandleEvents();
}

bool EventManager::HasCloseEvent() const {
    return has_close_event_;
}

const std::pair<Vector2D, bool>& EventManager::get_click_event() const {
    return click_event_;
}

const std::optional<MouseWheelInfo>& EventManager::get_mouse_wheel_event() const {
    return mouse_wheel_event_;
}

bool EventManager::HasKeyPressBackspaceEvent() const {
    return has_key_press_backspace_event_;
}

bool EventManager::HasKeyPressEnterEvent() const {
    return has_key_press_enter_event_;
}

ArrowsKeyPressInfo EventManager::GetArrowKeyPressEvent() const {
    return arrows_info_;
}
