#include <source/drawable_objects/drawable_object.h>
#include <source/utility/segment.h>

class SelectionBorder : public DrawableObject {
    std::vector<std::pair<Vector2D, u_int8_t>> segments_;
    Segment CalculateSegment(Vector2D pos, u_int8_t side, const GameOptions&);
public:
    void Clear();
    void AddLine(Vector2D pos, u_int8_t side);
    void Draw(Screen&, const GameOptions&) override;
};
