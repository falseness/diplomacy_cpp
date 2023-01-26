#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>
#include "source/drawable_objects_groups/game_scene/grid_logic_helper.h"

class Grid;

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<std::pair<int, int>, u_int8_t>> segments_;
    const Grid& grid_;
    Color line_color_;
    const bool draw_centered_;
    const float border_width_multiply_ratio_;
    Segment CalculateSegment(std::pair<int, int>, u_int8_t side, Screen& screen, const GameOptions&);
    void AddLine(std::pair<int, int>, u_int8_t side);
public:
    inline void set_line_color(Color line_color) {
        line_color_ = line_color;
    }
    void Clear();
    void SelectCell(std::pair<int, int> coord);
    SelectionBorder(const Grid&, Color line_color, float border_width_multiply_ratio = 1.0, bool draw_centered=true);
    void UpdateBorder(const std::vector<std::pair<int, int>> &visited_cells, const GridLogicHelper &logic_helper);

    void Draw(Screen&, const GameOptions&) override;
};

class TwoLayersSelectionBorder : public DrawableObject {
    SelectionBorder outer_border_;
    SelectionBorder inner_border_;
public:
    inline void set_inner_line_color(Color line_color) {
        inner_border_.set_line_color(line_color);
    }
    inline void Clear() {
        outer_border_.Clear();
        inner_border_.Clear();
    }
    inline void SelectCell(std::pair<int, int> coord) {
        outer_border_.SelectCell(coord);
        inner_border_.SelectCell(coord);
    }
    TwoLayersSelectionBorder(const Grid& grid, Color outer_line_color, Color inner_line_color,
                    float outer_border_width_multiply_ratio = 2.0, float inner_border_width_multiply_ratio = 1.0);
    inline void UpdateBorder(const std::vector<std::pair<int, int>> &visited_cells, const GridLogicHelper &logic_helper) {
        outer_border_.UpdateBorder(visited_cells, logic_helper);
        inner_border_.UpdateBorder(visited_cells, logic_helper);
    }
    inline void Draw(Screen& screen, const GameOptions& game_options) override {
        outer_border_.Draw(screen, game_options);
        inner_border_.Draw(screen, game_options);
    }
};