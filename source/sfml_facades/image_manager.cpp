#include "image_manager.h"

void ImageManager::load_all_images() {
    images["peasant"] = sf::Texture();
    images["peasant"].loadFromFile("assets/entities/units/peasant.png");
}

ImageManager::ImageManager() {
    load_all_images();
}