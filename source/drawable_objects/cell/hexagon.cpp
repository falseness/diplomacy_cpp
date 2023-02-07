#include "source/drawable_objects/cell/hexagon.h"
#include "source/options/game.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"

Hexagon::Hexagon(const Cell& cell) : cell_(cell) {}

void Hexagon::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D position = cell_.get_pos(game_options);

    HexagonOptions hexagon_options(game_options.hexagon_options);
    hexagon_options.fill_color = cell_.get_color();

    screen.DrawOnHexagonBuffer(hexagon_options, position, 1.0f);
    //screen.DrawHexagon(hexagon_options, position, 1.0f);
    if (!cell_.is_suburb()) {
        hexagon_options.fill_color = Color::kWhite;
        screen.DrawOnHexagonBuffer(hexagon_options, position, Cell::kColorAlphaRatio);
    }
}

Segment Hexagon::get_side(uint8_t side_index, Screen& screen, const GameOptions& game_options) const {
    Vector2D point1 = screen.get_point_of_hexagon(side_index, game_options.hexagon_options, cell_.get_pos(game_options),
                                Cell::kColorAlphaRatio);

    Vector2D point2 = screen.get_point_of_hexagon((side_index + 1) % GridCells::kHexagonMaximumNeighbours,
                                                  game_options.hexagon_options, cell_.get_pos(game_options),
                                                  Cell::kColorAlphaRatio);
    return {point1, point2};
}
