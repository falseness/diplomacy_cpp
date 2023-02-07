#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/utility/color.h>


// we may use copy constructor, but I don't want do change classes of external library
template <typename ColorType1, typename ColorType2>
inline ColorType1 create_color(const ColorType2& color) {
    return ColorType1(color.red, color.green, color.blue);
}

template <typename VecType1, typename VecType2>
inline VecType1 create_vector(const VecType2& vec) {
    return {vec.x, vec.y};
}
