#include <source/drawable_objects/cell/hexagon.h>
#include <source/options/options.h>
#include <source/drawable_objects/cell/cell.h>

Hexagon::Hexagon(const Cell& cell) : cell_(cell) {}

void Hexagon::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D position = cell_.get_pos(game_options);

    HexagonOptions hexagon_options(game_options.hexagon_options);
    hexagon_options.fill_color = cell_.get_color();
    screen.DrawHexagon(hexagon_options, position);
}
