#include "text.h"
#include <source/sfml_facades/screen.h>

void Text::Draw(Screen& screen, const GameOptions &) {
    if (!text.empty()) {
        screen.DrawText(*this);
    }
}

float Text::get_height(const Screen& screen) const {
    return screen.get_height_of(*this);
}

float Text::get_width(const Screen& screen) const {
    return screen.get_width_of(*this);
}

void Text::Draw(Screen &screen, const GameOptions &game_options, float thickness, Color outline_color) {
    if (!text.empty()) {
        screen.DrawText(*this, thickness, outline_color);
    }
}

void RightAlignedText::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D transition = {get_width(screen), 0};
    position -= transition;
    Text::Draw(screen, game_options);
    screen.DrawText(*this);
    position += transition;
}
