#include "screen.h"
#include <source/sfml_facades/utility/sfml_color.h>

Screen::Screen(sf::RenderWindow& window) :
            width_(sf::VideoMode::getDesktopMode().width),
            height_(sf::VideoMode::getDesktopMode().height),
            window_(window) {
    window_.create(sf::VideoMode(width_, height_), "Diplomacy");
    background_color_ = sf::Color(80, 80, 80);
}
void Screen::Clear() {
    window_.clear(background_color_);
}

void Screen::Draw(const sf::Shape& shape) {
    window_.draw(shape);
}

void Screen::DrawHexagon(const HexagonOptions& hexagon_options, const Point& position) {
    hexagon_shape_.setRadius(hexagon_options.radius);
    hexagon_shape_.setFillColor(create_color(hexagon_options.fill_color));
    hexagon_shape_.setOutlineColor(create_color(hexagon_options.outline_color));
    hexagon_shape_.setOutlineThickness(hexagon_options.outline_thickness);
    hexagon_shape_.setRotation(hexagon_options.rotation);

    hexagon_shape_.setPosition(position.x, position.y);
    Draw(hexagon_shape_);
}

void Screen::Display() {
    window_.display();
}
bool Screen::IsOpen() const {
    return window_.isOpen();
}
void Screen::Close() {
    window_.close();
}
