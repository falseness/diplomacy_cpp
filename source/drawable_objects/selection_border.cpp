#include "selection_border.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include <cmath>
#include <cassert>

void SelectionBorder::Draw(Screen& screen, const GameOptions& game_options) {
    static const float kBorderWidthToRadiusRatio = 0.075f;
    const float border_width = game_options.hexagon_options.radius * kBorderWidthToRadiusRatio *
            border_width_multiply_ratio_;

    for (auto encoded_segment : segments_) {
        auto segment = CalculateSegment(encoded_segment.first, encoded_segment.second, screen, game_options);
        if (draw_centered_) {
            screen.DrawCenteredLine(segment.pos1, segment.pos2, border_width, line_color_);
        }
        else {
            screen.DrawLine(segment.pos1, segment.pos2, border_width, line_color_);
        }
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

SelectionBorder::SelectionBorder(const Grid& grid, Color line_color, float border_width_multiply_ratio,
                                 bool draw_centered) : grid_(grid), line_color_(line_color),
                                 border_width_multiply_ratio_(border_width_multiply_ratio),
                                 draw_centered_(draw_centered) {}

void SelectionBorder::UpdateBorder(const std::vector<std::pair<int, int>> &visited_cells,
                                   const GridLogicHelper &logic_helper) {
    Clear();
    for (auto coord : visited_cells) {
        assert(logic_helper.is_visited(coord));
        auto neighbours = grid_.get_neighbours(coord);
        for (size_t i = 0; i < neighbours.size(); ++i) {
            if (grid_.is_coord_out_of_range(neighbours[i]) || !logic_helper.is_visited(neighbours[i]))
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

TwoLayersSelectionBorder::TwoLayersSelectionBorder(const Grid &grid, Color outer_line_color, Color inner_line_color,
   float outer_border_width_multiply_ratio, float inner_border_width_multiply_ratio) :
   outer_border_(grid, outer_line_color, outer_border_width_multiply_ratio, true),
   inner_border_(grid, inner_line_color, inner_border_width_multiply_ratio, true){

}
