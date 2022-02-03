#include "text.h"
#include <source/sfml_facades/screen.h>

void Text::Draw(Screen& screen, const GameOptions &) {
    screen.DrawText(*this);
}

float Text::get_height(const Screen& screen) const {
    return screen.get_height_of(*this);
}

float Text::get_width(const Screen& screen) const {
    return screen.get_width_of(*this);
}

void Text::set_center(Vector2D center, const Screen& screen) {
    position = {center.x - get_width(screen) / 2, center.y - get_height(screen) / 2};
}

void RightAlignedText::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D transition = {get_width(screen), 0};
    position -= transition;
    Text::Draw(screen, game_options);
    screen.DrawText(*this);
    position += transition;
}
