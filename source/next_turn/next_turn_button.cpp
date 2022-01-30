#include "next_turn_button.h"

void NextTurnButton::Draw(Screen& screen, const GameOptions &) {
    screen.DrawTriangle(*this);
}
