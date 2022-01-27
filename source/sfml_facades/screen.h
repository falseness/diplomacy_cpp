#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/options/hexagon.h>
#include <source/sfml_facades/image_manager.h>
#include <source/utility/object_size.h>

#pragma once

class RoundedRectangle;

class Screen {
    sf::RenderWindow& window_;
    sf::Color background_color_;

    sf::CircleShape hexagon_shape_ = sf::CircleShape(0, 6);

    ImageManager image_manager_ = ImageManager();

    Vector2D draw_offset_ = Vector2D(0, 0);
    size_t width_;
    size_t height_;
public:
    Screen(sf::RenderWindow& window);
    void Clear();
    void DrawHexagon(const HexagonOptions&, const Vector2D&);
    void DrawRoundedRectangle(const RoundedRectangle&);
    void DrawImage(const std::string&, const ObjectSize&, const Vector2D&);
    void Display();
    bool IsOpen() const;
    void Close();
    void set_draw_offset(const Vector2D&);
    const Vector2D& get_draw_offset() const;

    size_t get_width() const;
    size_t get_height() const;
};
