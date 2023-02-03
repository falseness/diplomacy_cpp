#include "source/utility/vector2d.h"


struct Rectangle {
    float minimum_x;
    float minimum_y;
    float maximum_x;
    float maximum_y;

    // top means minimum_y
    inline Vector2D top_left_corner() const {
        return {minimum_x, minimum_y};
    }

    inline Vector2D top_right_corner() const {
        return {maximum_x, minimum_y};
    }

    inline Vector2D bottom_left_corner() const {
        return {minimum_x, maximum_x};
    }

    inline Vector2D bottom_right_corner() const {
        return {maximum_x, maximum_y};
    }
};