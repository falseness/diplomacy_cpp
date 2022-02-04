#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>

class Grid;

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<Vector2D, u_int8_t>> segments_;
    const Grid& grid_;
    static Segment CalculateSegment(Vector2D pos, u_int8_t side, const GameOptions&);

    void Clear();
    void AddLine(Vector2D pos, u_int8_t side);
public:
    explicit SelectionBorder(const Grid&);
    void UpdateBorder(const GameOptions& game_options);

    void Draw(Screen&, const GameOptions&) override;
};
