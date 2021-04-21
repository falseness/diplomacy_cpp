#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>

#pragma once

class ImageManager {
public:
    std::unordered_map<std::string, sf::Texture> images;
private:
    void load_all_images();
public:
    ImageManager();
};