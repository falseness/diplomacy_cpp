#include "triangle.h"

std::vector<Vector2D> Triangle::get_points() const {
    std::vector<Vector2D> result;
    result.emplace_back(position.x - side / 2, position.y - side / 2);
    result.emplace_back(position.x + side / 2, position.y);
    result.emplace_back(position.x - side / 2, position.y + side / 2);
    return std::move(result);
}

bool Triangle::is_inside(const Vector2D& pos) const {
    int8_t signs_sum = 0;
    auto points = get_points();
    for (int i = 0; i < points.size(); ++i) {
        Vector2D side_vector = points[(i + 1) == points.size() ? 0 : (i + 1)] - points[i];
        signs_sum += get_sign(cross_product(points[i] - pos, side_vector));
    }
    return abs(signs_sum) == points.size();
}
