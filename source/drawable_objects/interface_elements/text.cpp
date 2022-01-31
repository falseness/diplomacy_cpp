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
