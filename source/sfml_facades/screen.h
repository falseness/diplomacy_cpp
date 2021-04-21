#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/options/hexagon.h>
#include <source/sfml_facades/image_manager.h>

#pragma once

class Screen {
    sf::RenderWindow& window_;
    sf::Color background_color_;

    sf::CircleShape hexagon_shape_ = sf::CircleShape(0, 6);

    ImageManager image_manager_ = ImageManager();
public:
    size_t width_;
    size_t height_;
    Screen(sf::RenderWindow& window);
    void Clear();
    void DrawHexagon(const HexagonOptions&, const Point&);
    void DrawImage(const std::string&, const Point&);
    void Display();
    bool IsOpen() const;
    void Close();
};
