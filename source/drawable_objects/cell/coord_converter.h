#include <tuple>
#include <source/utility/vector2d.h>
#include <source/options/options.h>
#include <vector>

#pragma once

class CoordConverter {
    static std::vector<std::pair<int, int>> CalculateNearestHexagons(const std::pair<int, int>&);
    static std::pair<int, int> ChooseNearestHexagon(const std::vector<std::pair<int, int>>&, const Vector2D&,
                                                 const GameOptions&);
public:
    static std::pair<int, int> BiasToTransition(int x, int y);
    static std::pair<int, int> TransitionToBias(const std::pair<int, int>&);
    static std::pair<int, int> CalculateCoord(const Vector2D& pos, const GameOptions& game_options);
    static bool IsCoordOutOfRange(const std::pair<int, int>&, size_t, size_t);
};
