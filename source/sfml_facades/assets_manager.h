#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>

#pragma once

class AssetsManager {
public:
    std::unordered_map<std::string, sf::Texture> images_;
    std::unordered_map<std::string, sf::Font> fonts_;
private:
    void load_all_images();
    void load_all_fonts();
public:
    AssetsManager();
};