#include "sfml_color.h"

sf::Color create_color(const Color& color) {
    return sf::Color(color.red, color.green, color.blue);
}