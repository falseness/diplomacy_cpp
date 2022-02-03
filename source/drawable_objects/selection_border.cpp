#include "selection_border.h"

#include <cmath>

void SelectionBorder::Draw(Screen &, const GameOptions& game_options) {
    static const Color kLineColor = Color::kWhite;
    const float border_width = game_options.hexagon_options.radius * 0.05f;

}

void SelectionBorder::AddLine(Vector2D pos, u_int8_t side) {
    segments_.emplace_back(pos, side);
}

Segment SelectionBorder::CalculateSegment(Vector2D pos, u_int8_t side, const GameOptions& game_options) {
    float radius = game_options.hexagon_options.radius;
    static const u_int8_t kHexagonSidesCount = 6;
    const float kLinesVariants[kHexagonSidesCount][2][2] = {
    {
        {-radius / 2, -radius / 2 * static_cast<float>(sqrt(3))},
        {radius / 2, -radius / 2 * static_cast<float>(sqrt(3))}
    },
    {
        {radius / 2, -radius / 2 * static_cast<float>(sqrt(3))},
        {radius, 0}
    },
    {
        {radius, 0},
        {radius / 2, radius / 2 * static_cast<float>(sqrt(3))}
    },
    {
        {radius / 2, radius / 2 * static_cast<float>(sqrt(3))},
        {-radius / 2, radius / 2 * static_cast<float>(sqrt(3))}
    },
    {
        {-radius / 2, radius / 2 * static_cast<float>(sqrt(3))},
        {-radius, 0}
    },
    {
        {-radius, 0},
        {-radius / 2, -radius / 2 * static_cast<float>(sqrt(3))}
    }
    };
    Segment result{Vector2D(kLinesVariants[side][0][0], kLinesVariants[side][0][1]),
                   Vector2D(kLinesVariants[side][1][0], kLinesVariants[side][1][1])};
    result.pos1 += pos;
    result.pos2 += pos;
    return result;
}

void SelectionBorder::Clear() {
    segments_.clear();
}
