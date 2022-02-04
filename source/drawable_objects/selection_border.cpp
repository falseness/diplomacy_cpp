#include "selection_border.h"
#include <source/drawable_objects_groups/game_scene/grid.h>
#include <cmath>
#include <cassert>

void SelectionBorder::Draw(Screen& screen, const GameOptions& game_options) {
    static const Color kLineColor = Color::kWhite;
    const float border_width = game_options.hexagon_options.radius * 0.075f;

    for (auto encoded_segment : segments_) {
        auto segment = CalculateSegment(encoded_segment.first, encoded_segment.second, screen, game_options);
        screen.DrawLine(segment.pos1, segment.pos2, border_width, kLineColor);
    }
}

void SelectionBorder::AddLine(std::pair<int, int> coord, u_int8_t side) {
    segments_.emplace_back(coord, side);
}

Segment SelectionBorder::CalculateSegment(std::pair<int, int> coord, u_int8_t side, Screen& screen,
                                          const GameOptions& game_options) {
    return grid_.get_cell(coord)->get_side(side, screen, game_options);
}

void SelectionBorder::Clear() {
    segments_.clear();
}

SelectionBorder::SelectionBorder(const Grid& grid) : grid_(grid) {}

void SelectionBorder::UpdateBorder(const std::vector<std::pair<int, int>>& visited_cells) {
    Clear();
    for (auto coord : visited_cells) {
        assert(grid_.logic_helper_.is_visited(coord));
        auto neighbours = grid_.get_neighbours(coord);
        for (size_t i = 0; i < neighbours.size(); ++i) {
            if (grid_.is_coord_out_of_range(neighbours[i]) || !grid_.logic_helper_.is_visited(neighbours[i]))
                AddLine(coord, i);
        }
    }
}

void SelectionBorder::SelectCell(std::pair<int, int> coord) {
    Clear();
    for (size_t i = 0; i < Grid::kHexagonMaximumNeighbours; ++i) {
        AddLine(coord, i);
    }
}
