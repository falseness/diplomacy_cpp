//
// Created by nikita on 31.01.2022.
//

#include "rounded_rectangle_with_text.h"
#include "switch_button.h"

void RoundedRectangleWithText::Draw(Screen& screen, const GameOptions& game_options) {
    RoundedRectangle::Draw(screen, game_options);
    text.set_center(get_center(), screen);
    text.Draw(screen, game_options);
}
