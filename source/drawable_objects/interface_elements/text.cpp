#include "text.h"

void Text::Draw(Screen& screen, const GameOptions &) {
    screen.DrawText(*this);
}
