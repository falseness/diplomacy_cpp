#include <source/sprites/cell/hexagon.h>
#include <source/options/options.h>
#include <source/sprites/cell/cell.h>

Hexagon::Hexagon(const Cell& cell) : cell_(cell) {}

void Hexagon::Draw(Screen& screen, const GameOptions& game_options) {
    Point position = cell_.calculate_pos(game_options);
    screen.DrawHexagon(game_options.hexagon_options, position);
}
