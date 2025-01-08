#include "rounded_rectangle.h"


void RoundedRectangle::Draw(Screen& screen, const GameOptions &) {
    screen.DrawRoundedRectangle(*this);
}

