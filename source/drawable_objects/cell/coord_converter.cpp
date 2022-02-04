#include "coord_converter.h"
#include <cmath>
#include <vector>
#include <source/utility/geometry.h>

std::pair<int, int> CoordConverter::BiasToTransition(int x, int y) {
    /*
        even basis
        y = y - (x - (x & 1)) / 2 (to axial)
        by = 2 * y + x
    */
    return std::make_pair(x, 2 * y + (x & 1));
}

std::pair<int, int> CoordConverter::TransitionToBias(const std::pair<int, int>& coord) {
    return std::make_pair(coord.first, (coord.second - (coord.first & 1)) / 2);
}


std::vector<std::pair<int, int>> CoordConverter::CalculateNearestHexagons(
        const std::pair<int, int>& transition_coord) {
    const size_t nearest_hexagons_count = 4;
    int nearest_hexagons_offset[nearest_hexagons_count][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    std::vector<std::pair<int, int>> nearest_hexagons(nearest_hexagons_count);
    for (size_t i = 0; i  < nearest_hexagons.size(); ++i) {
        nearest_hexagons[i] = std::make_pair(transition_coord.first + nearest_hexagons_offset[i][0],
                                             transition_coord.second + nearest_hexagons_offset[i][1]);
    }
    return nearest_hexagons;
}

std::pair<int, int> CoordConverter::ChooseNearestHexagon(
        const std::vector<std::pair<int, int>>& nearest_hexagons,
        const Vector2D& pos, const GameOptions& game_options) {
    size_t nearest_hexagon_index = nearest_hexagons.size();
    float min_distance = game_options.hexagon_options.radius * game_options.hexagon_options.radius;

    for (size_t i = 0; i < nearest_hexagons.size(); ++i) {
        Vector2D hex_pos = {static_cast<float>(nearest_hexagons[i].first) * game_options.hexagon_offset.x,
                         static_cast<float>(nearest_hexagons[i].second) * game_options.hexagon_offset.y};
        float distance = Geometry::PythagoreanSquared(hex_pos.x - pos.x, hex_pos.y - pos.y);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_hexagon_index = i;
        }
    }
    return nearest_hexagons.at(nearest_hexagon_index);
}

std::pair<int, int> CoordConverter::CalculateCoord(const Vector2D& pos, const GameOptions& game_options) {
    std::pair<int, int> transition_coord = std::make_pair(round(pos.x / game_options.hexagon_offset.x),
                                                          round(pos.y / game_options.hexagon_offset.y));
    if ((transition_coord.first & 1) == (transition_coord.second & 1))
        return TransitionToBias(transition_coord);

    std::vector<std::pair<int, int>> nearest_hexagons = CalculateNearestHexagons(transition_coord);
    std::pair<int, int> result_transition_coord = ChooseNearestHexagon(nearest_hexagons, pos, game_options);
    return TransitionToBias(result_transition_coord);
}

bool CoordConverter::IsCoordOutOfRange(const std::pair<int, int>& coord, size_t arr_size_n, size_t arr_size_m) {
    return coord.first < 0 || coord.second < 0 || coord.first >= arr_size_n || coord.second >= arr_size_m;
}
