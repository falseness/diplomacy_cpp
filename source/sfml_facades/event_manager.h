#include <source/utility/vector2d.h>

#pragma once

class EventManager {
    static const sf::Keyboard::Key kKeyboardPressBackspaceButton = sf::Keyboard::Backspace;
    static const sf::Keyboard::Key kKeyboardPressEnterButton = sf::Keyboard::Enter;
    sf::RenderWindow& window_;
    void HandleEvents();
    bool has_close_event_;
    bool has_key_press_backspace_event_;
    bool has_key_press_enter_event_;
    std::pair<Vector2D, bool> click_event_;
    static const std::pair<Vector2D, bool> no_click_event_;
public:
    void NextIteration();
    explicit EventManager(sf::RenderWindow& window);
    bool HasCloseEvent();
    [[nodiscard]] bool HasKeyPressBackspaceEvent() const;
    [[nodiscard]] bool HasKeyPressEnterEvent() const;
    const std::pair<Vector2D, bool>& get_click_event();
};
