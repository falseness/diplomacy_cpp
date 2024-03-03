#include "source/utility/vector2d.h"
#include "source/utility/event_info.h"


#pragma once

class EventManager {
    static const sf::Keyboard::Key kKeyboardPressBackspaceButton = sf::Keyboard::Backspace;
    static const sf::Keyboard::Key kKeyboardPressEnterButton = sf::Keyboard::Enter;
    sf::RenderWindow& window_;
    void HandleEvents();
    bool has_close_event_;
    bool has_key_press_backspace_event_;
    bool has_key_press_enter_event_;
    ArrowsKeyPressInfo arrows_info_{0, 0};
    std::pair<Vector2D, bool> click_event_;
    std::optional<MouseWheelInfo> mouse_wheel_event_;
    static const std::pair<Vector2D, bool> no_click_event_;
public:
    void NextIteration();
    explicit EventManager(sf::RenderWindow& window);
    bool HasCloseEvent() const;
    [[nodiscard]] bool HasKeyPressBackspaceEvent() const;
    [[nodiscard]] bool HasKeyPressEnterEvent() const;
    // horizontal sum indicates that left or right arrow is pressed. -1 for left arrow and +1 for right arrow
    // 0 for no arrow. same works for vertical_sum where -1 means up arrow is pressed and 1 means down arrow
    // also the same works for WASD buttons where W corresponds to up arrow, s corresponds to left arrow etc.
    [[nodiscard]] ArrowsKeyPressInfo GetArrowKeyPressEvent() const;
    const std::pair<Vector2D, bool>& get_click_event() const;
    const std::optional<MouseWheelInfo>& get_mouse_wheel_event() const;
};
