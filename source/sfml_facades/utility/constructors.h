#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/utility/color.h>


// we may use copy constructor, but I don't want do change classes of external library

inline sf::Color create_color(const Color& color) {
    return sf::Color(color.red, color.green, color.blue);
}

inline sf::Vector2f create_vector(const Vector2D& vec) {
    return {vec.x, vec.y};
}