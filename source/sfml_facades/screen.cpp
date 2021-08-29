#include "screen.h"
#include <source/sfml_facades/utility/sfml_color.h>

Screen::Screen(sf::RenderWindow& window) :
            width_(sf::VideoMode::getDesktopMode().width),
            height_(sf::VideoMode::getDesktopMode().height),
            window_(window), background_color_(sf::Color(80, 80, 80)) {
    window_.create(sf::VideoMode(width_, height_), "Diplomacy");
}
void Screen::Clear() {
    window_.clear(background_color_);
}

void Screen::DrawHexagon(const HexagonOptions& hexagon_options, const Vector2D& position) {
    hexagon_shape_.setRadius(hexagon_options.radius);
    hexagon_shape_.setFillColor(create_color(hexagon_options.fill_color));
    hexagon_shape_.setOutlineColor(create_color(hexagon_options.outline_color));
    hexagon_shape_.setOutlineThickness(hexagon_options.outline_thickness);

    hexagon_shape_.setRotation(hexagon_options.rotation);
    hexagon_shape_.setPosition(position.x + hexagon_options.radius + draw_offset_.x,
                               position.y - hexagon_options.radius + draw_offset_.y);

    window_.draw(hexagon_shape_);
}

void Screen::DrawImage(const std::string& image_name, const ObjectSize& image_size, const Vector2D& position) {
    sf::Sprite sprite;
    sprite.setTexture(image_manager_.images[image_name]);

    sf::FloatRect this_rect = sprite.getGlobalBounds();
    sprite.scale(image_size.width / this_rect.width, image_size.height / this_rect.height);
    sprite.setPosition(position.x - image_size.width / 2 + draw_offset_.x,
                       position.y - image_size.height / 2 + draw_offset_.y);

    window_.draw(sprite);
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

void Screen::set_draw_offset(const Vector2D& offset) {
    draw_offset_ = offset;
}

const Vector2D& Screen::get_draw_offset() const {
    return draw_offset_;
}
