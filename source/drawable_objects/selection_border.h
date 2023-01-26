#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>
#include "source/drawable_objects_groups/game_scene/grid_logic_helper.h"

class Grid;

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<std::pair<int, int>, u_int8_t>> segments_;
    const Grid& grid_;
    const Color line_color_;
    const float border_width_multiply_ratio_;
    Segment CalculateSegment(std::pair<int, int>, u_int8_t side, Screen& screen, const GameOptions&);
    void AddLine(std::pair<int, int>, u_int8_t side);
public:
    void Clear();
    void SelectCell(std::pair<int, int> coord);
    SelectionBorder(const Grid&, Color line_color, float border_width_multiply_ratio = 1.0);
    void UpdateBorder(const std::vector<std::pair<int, int>> &visited_cells, const GridLogicHelper &logic_helper);

    void Draw(Screen&, const GameOptions&) override;
};
