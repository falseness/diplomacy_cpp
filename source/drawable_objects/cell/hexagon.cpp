#include <source/drawable_objects/cell/hexagon.h>
#include "source/options/game.h"
#include <source/drawable_objects/cell/cell.h>

Hexagon::Hexagon(const Cell& cell) : cell_(cell) {}

void Hexagon::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D position = cell_.get_pos(game_options);

    HexagonOptions hexagon_options(game_options.hexagon_options);
    hexagon_options.fill_color = cell_.get_color();

    screen.DrawHexagon(hexagon_options, position, 1.0f);
    if (!cell_.is_suburb()) {
        hexagon_options.fill_color = Color::kWhite;
        screen.DrawHexagon(hexagon_options, position, Cell::kColorAlphaRatio);
    }
}
