#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/options/hexagon.h>
#include <source/sfml_facades/assets_manager.h>
#include <source/utility/object_size.h>

#pragma once

class RoundedRectangle;
class Text;
class Triangle;

class Screen {
    sf::RenderWindow& window_;
    sf::Color background_color_;

    sf::CircleShape hexagon_shape_ = sf::CircleShape(0, 6);

    AssetsManager assets_manager_ = AssetsManager();

    Vector2D draw_offset_ = Vector2D(0, 0);
    size_t width_;
    size_t height_;
    sf::Text get_sfml_text(const Text&) const;
    void set_hexagon_shape(const HexagonOptions&, const Vector2D&, float);
    static void ChangeSprite(sf::Sprite& sprite, const ObjectSize &image_size, const Vector2D &position);
    Vector2D get_real_position_on_grid(const Vector2D& position);
    sf::Sprite get_sprite(const std::string &image_name, const ObjectSize &image_size, const Vector2D &position);
public:
    explicit Screen(sf::RenderWindow& window);
    void Clear();
    void DrawHexagon(const HexagonOptions&, const Vector2D&, float);
    void DrawTriangle(const Triangle&);
    void DrawRoundedRectangle(const RoundedRectangle&);
    void DrawImage(const std::string &image_name, const ObjectSize &image_size, const Vector2D &position);
    void DrawGridImage(const std::string &image_name, const ObjectSize &image_size, const Vector2D &position);
    void DrawGridImageWithOpactiy(const std::string &image_name, const ObjectSize &image_size,
                                  const Vector2D &position, float opacity);
    void DrawVerticalLine(float x, float y_bottom, float y_up, float width, Color color);
    void DrawLine(Vector2D begin, Vector2D end, float width, Color color);
    void DrawText(const Text&);
    void Display();
    bool IsOpen() const;
    void Close();
    void set_draw_offset(const Vector2D&);
    const Vector2D& get_draw_offset() const;
    float get_height_of(const Text&) const;
    float get_width_of(const Text&) const;
    Vector2D get_point_of_hexagon(uint8_t point, const HexagonOptions&, const Vector2D&, float);

    size_t get_width() const;
    size_t get_height() const;
};
