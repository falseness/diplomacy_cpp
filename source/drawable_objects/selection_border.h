#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>

class Grid;

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<std::pair<int, int>, u_int8_t>> segments_;
    const Grid& grid_;
    Segment CalculateSegment(std::pair<int, int>, u_int8_t side, Screen& screen, const GameOptions&);

    void Clear();
    void AddLine(std::pair<int, int>, u_int8_t side);
public:
    explicit SelectionBorder(const Grid&);
    void UpdateBorder(const GameOptions& game_options);

    void Draw(Screen&, const GameOptions&) override;
};
