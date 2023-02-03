#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "source/utility/rectangle.h"
#include "source/utility/set_additional_functions.h"


class AssetsManager {
    std::unordered_map<std::string, sf::Texture> images_;
    std::unordered_map<std::string, sf::Sprite> sprites_;
    sf::Texture all_images_;
    std::unordered_map<std::string, Rectangle> position_on_texture_;
    sf::RenderStates tmp_;
public:
    std::unordered_map<std::string, sf::Font> fonts_;
private:
    void load_image(const std::string& name, const std::string& path);
    void load_all_images();
    void load_all_fonts();
public:
    AssetsManager();
    [[nodiscard]] inline const Rectangle& get_position_on_texture(const std::string& image_name) const {
        return position_on_texture_.find(image_name)->second;
    }
    [[nodiscard]] sf::Texture* get_all_images_texture() {
        return &all_images_;
    }
    [[nodiscard]] inline sf::Sprite& get_sprite(const std::string& image_name) {
        return sprites_[image_name];
    }
    [[nodiscard]] inline sf::RenderStates& get_render_states() {
        return tmp_;
    }
};