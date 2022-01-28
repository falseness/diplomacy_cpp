#include "assets_manager.h"

void AssetsManager::load_all_images() {
    images_["peasant"] = sf::Texture();
    images_["peasant"].loadFromFile("entities/units/peasant.png");
    images_["debug"] = sf::Texture();
    images_["debug"].loadFromFile("entities/debug_image.png");
}

void AssetsManager::load_all_fonts() {
    fonts_["times new roman"] = sf::Font();
    fonts_["times new roman"].loadFromFile("fonts/times_new_roman.ttf");
}

AssetsManager::AssetsManager() {
    load_all_fonts();
    load_all_images();

}


