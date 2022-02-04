#include "screen.h"
#include <source/sfml_facades/utility/sfml_color.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/triangle.h>
#include <cmath>
#include <source/utility/geometry.h>
#include <cassert>

Screen::Screen(sf::RenderWindow& window) :
            width_(sf::VideoMode::getDesktopMode().width),
            height_(sf::VideoMode::getDesktopMode().height),
            window_(window), background_color_(sf::Color(80, 80, 80)) {
    window_.create(sf::VideoMode(width_, height_), "Diplomacy");
}
void Screen::Clear() {
    window_.clear(background_color_);
}

void Screen::DrawHexagon(const HexagonOptions& hexagon_options, const Vector2D& position, float opacity) {
    set_hexagon_shape(hexagon_options, position, opacity);
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
    window_.draw(get_sfml_text(text));
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

float Screen::get_width_of(const Text& text) const {
    return get_sfml_text(text).getLocalBounds().width;
}

float Screen::get_height_of(const Text& text) const {
    // sfml function doesnt work properly is text doesnt contain all symbols
    std::string all_symbols_string;
    for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
        all_symbols_string += symbol;
    }
    Text other(text);
    other.text = all_symbols_string;
    return get_sfml_text(other).getLocalBounds().height;
}

sf::Text Screen::get_sfml_text(const Text & text) const {
    static const std::string kFontName = "times new roman";
    sf::Text sfml_text;

    sfml_text.setFont(assets_manager_.fonts_.find(kFontName)->second);
    sfml_text.setString(text.text);
    sfml_text.setCharacterSize(text.size);
    sfml_text.setFillColor(create_color(text.color));

    sfml_text.setOrigin(sfml_text.getGlobalBounds().left, sfml_text.getGlobalBounds().top);
    sfml_text.setPosition(text.position.x, text.position.y);
    return sfml_text;
}

void Screen::DrawVerticalLine(float x, float y_bottom, float y_up, float width, Color color) {
    sf::RectangleShape rect;
    rect.setFillColor(create_color(color));
    float height = y_bottom - y_up;
    assert(height >= 0);
    rect.setSize({width, height});
    rect.setPosition(x, y_up);

    window_.draw(rect);
}

void Screen::DrawLine(Vector2D begin, Vector2D end, float width, Color color) {
    Vector2D dt = end - begin;
    float angle = atan2f(dt.y, dt.x);

    sf::RectangleShape line({dt.get_length(), width});
    line.setFillColor(create_color(color));

    line.setRotation(Geometry::RadiansToDegrees(angle));
    line.setPosition(begin.x, begin.y);

    window_.draw(line);
}

Vector2D Screen::get_point_of_hexagon(uint8_t point, const HexagonOptions& hexagon_options, const Vector2D& position,
                                      float opacity) {
    // need shift to synchronize order with Grid::get_neighbours()
    static const uint8_t kPointsShift = 4;


    HexagonOptions my_hexagon_options = hexagon_options;
    my_hexagon_options.radius += my_hexagon_options.outline_thickness;
    set_hexagon_shape(my_hexagon_options, position, opacity);
    auto sfml_result = hexagon_shape_.getTransform().transformPoint(
            hexagon_shape_.getPoint((point + kPointsShift) % hexagon_shape_.getPointCount()));
    Vector2D result = {sfml_result.x, sfml_result.y};
    return result;
}

void Screen::set_hexagon_shape(const HexagonOptions& hexagon_options, const Vector2D& position, float opacity) {
    hexagon_shape_.setRadius(hexagon_options.radius);

    auto sfml_color = sf::Color(hexagon_options.fill_color.red, hexagon_options.fill_color.green,
                                hexagon_options.fill_color.blue, static_cast<size_t>(opacity * 255));
    hexagon_shape_.setFillColor(sfml_color);

    hexagon_shape_.setOutlineColor(create_color(hexagon_options.outline_color));
    hexagon_shape_.setOutlineThickness(hexagon_options.outline_thickness);

    hexagon_shape_.setRotation(hexagon_options.rotation);
    hexagon_shape_.setPosition(position.x + hexagon_options.radius + draw_offset_.x,
                               position.y - hexagon_options.radius + draw_offset_.y);
}
