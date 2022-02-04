#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>

class Grid;

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<std::pair<int, int>, u_int8_t>> segments_;
    const Grid& grid_;
    Segment CalculateSegment(std::pair<int, int>, u_int8_t side, Screen& screen, const GameOptions&);

    void AddLine(std::pair<int, int>, u_int8_t side);
public:
    void Clear();
    void SelectCell(std::pair<int, int> coord);
    explicit SelectionBorder(const Grid&);
    void UpdateBorder(const std::vector<std::pair<int, int>>& visited_cells);

    void Draw(Screen&, const GameOptions&) override;
};
