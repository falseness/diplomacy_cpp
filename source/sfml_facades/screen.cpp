#include "screen.h"
#include <source/sfml_facades/utility/sfml_color.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/triangle.h>

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

void Screen::DrawImage(const std::string &image_name, const ObjectSize &image_size, const Vector2D &position) {
    sf::Sprite sprite;
    sprite.setTexture(assets_manager_.images_[image_name]);

    sf::FloatRect this_rect = sprite.getGlobalBounds();
    sprite.scale(image_size.width / this_rect.width, image_size.height / this_rect.height);
    sprite.setPosition(position.x - image_size.width / 2,
                       position.y - image_size.height / 2);

    window_.draw(sprite);
}

void Screen::DrawGridImage(const std::string& image_name, const ObjectSize& image_size, const Vector2D& position) {
    DrawImage(image_name, image_size, position + draw_offset_);
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


void Screen::DrawRoundedRectangle(const RoundedRectangle& rect) {
    // drawing rounded rectangle using four circles and two rectangles
    sf::CircleShape sfml_circle;
    sfml_circle.setRadius(rect.corner_radius);
    sfml_circle.setOutlineColor(create_color(rect.border_color));
    sfml_circle.setOutlineThickness(rect.border_width);
    sfml_circle.setFillColor(sf::Color::Transparent);

    std::vector<sf::Vector2f> transition_from_left_up_corner{
        {0, 0}, {rect.width - 2 * rect.corner_radius, 0},
        {rect.width - 2 * rect.corner_radius, rect.height - 2 * rect.corner_radius},
        {0, rect.height - 2 * rect.corner_radius}};
    for (auto pos_transition : transition_from_left_up_corner) {
        sfml_circle.setPosition(sf::Vector2f(rect.get_left(), rect.get_up()) + pos_transition);
        window_.draw(sfml_circle);
    }

    sf::RectangleShape sfml_rect;
    sfml_rect.setOutlineColor(create_color(rect.border_color));
    sfml_rect.setOutlineThickness(rect.border_width);
    sfml_rect.setFillColor(sf::Color::Transparent);

    std::vector<sf::RectangleShape> sfml_rects;

    sfml_rect.setPosition(rect.get_left(), rect.get_up() + rect.corner_radius);
    sfml_rect.setSize(sf::Vector2f(rect.width, rect.height - 2 * rect.corner_radius));

    sfml_rects.push_back(sfml_rect);

    sfml_rect.setPosition(rect.get_left() + rect.corner_radius, rect.get_up());
    sfml_rect.setSize(sf::Vector2f(rect.width - 2 * rect.corner_radius, rect.height));
    sfml_rects.push_back(sfml_rect);

    for (const auto& this_rect : sfml_rects) {
        window_.draw(this_rect);

    }
    for (auto& this_rect : sfml_rects) {
        this_rect.setFillColor(create_color(rect.background_color));
        this_rect.setOutlineColor(sf::Color::Transparent);
        window_.draw(this_rect);
    }
    sfml_circle.setFillColor(create_color(rect.background_color));
    sfml_circle.setOutlineColor(sf::Color::Transparent);
    for (auto pos_transition : transition_from_left_up_corner) {
        sfml_circle.setPosition(sf::Vector2f(rect.get_left(), rect.get_up()) + pos_transition);
        window_.draw(sfml_circle);
    }
}

size_t Screen::get_height() const {
    return height_;
}

size_t Screen::get_width() const {
    return width_;
}

void Screen::DrawText(const Text& text) {
    static const std::string kFontName = "times new roman";
    sf::Text sfml_text;
    sfml_text.setFont(assets_manager_.fonts_[kFontName]);
    sfml_text.setString(text.text);
    sfml_text.setCharacterSize(text.size);
    sfml_text.setFillColor(create_color(text.color));
    sfml_text.setPosition(text.position.x, text.position.y);
    window_.draw(sfml_text);
}

void Screen::DrawTriangle(const Triangle& triangle) {
    static const size_t kTrianglePointsCount = 3;
    sf::ConvexShape convex;
    convex.setPointCount(kTrianglePointsCount);
    auto points = triangle.get_points();
    for (size_t i = 0; i < points.size(); ++i) {
        convex.setPoint(i, {points[i].x, points[i].y});
    }
    convex.setOutlineColor(create_color(triangle.border_color));
    convex.setFillColor(create_color(triangle.background_color));
    convex.setOutlineThickness(triangle.border_width);
    window_.draw(convex);
}
