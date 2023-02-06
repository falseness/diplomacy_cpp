#include "assets_manager.h"

#include <cassert>


void AssetsManager::load_all_images() {
    load_image("peasant", "entities/units/peasant.png");

    load_image("archer", "entities/units/archer.png");

    load_image("swordsman", "entities/units/swordsman.png");
    load_image("cavalry", "entities/units/cavalry.png");

    load_image("catapult", "entities/units/catapult.png");

    load_image("town", "entities/buildings/town.png");

    load_image("barrack", "entities/buildings/barrack.png");

    load_image("farm", "entities/buildings/farm.png");

    load_image("wall", "entities/buildings/wall.png");
    load_image("tower", "entities/buildings/tower.png");

    load_image("gold", "other_images/gold.png");

    load_image("debug", "entities/debug_image.png");

    load_image("suburb", "other_images/suburb.png");

    load_image("mountain", "entities/buildings/mountain.png");
    load_image("lake", "entities/buildings/lake.png");
    load_image("sea", "entities/buildings/sea.png");
}

void AssetsManager::load_image(const std::string& name, const std::string& path) {
    images_[name] = sf::Texture();
    images_[name].loadFromFile(path);

    sprites_[name].setTexture(images_[name]);
}

void AssetsManager::load_all_fonts() {
    fonts_["times new roman"] = sf::Font();
    fonts_["times new roman"].loadFromFile("fonts/times_new_roman.ttf");
}

AssetsManager::AssetsManager() {
    load_all_fonts();
    load_all_images();

    unsigned int width = 0;
    unsigned int height = 0;
    for (const auto& [name, texture] : images_) {
        auto size = texture.getSize();
        width += size.x;
        if (size.y > height) {
            height = size.y;
        }
    }

    bool was_created = all_images_.create(width, height);
    assert(was_created);

    unsigned int pos_x = 0;

    static const unsigned int kPosY = 0;

    for (const auto& [name, texture] : images_) {
        all_images_.update(texture, pos_x, kPosY);
        auto size = texture.getSize();

        position_on_texture_[name] = {static_cast<float>(pos_x), static_cast<float>(kPosY),
                                      static_cast<float>(pos_x + size.x), static_cast<float>(kPosY + texture.getSize().y)};
        pos_x += size.x;
    }

    all_images_.setSmooth(false);
    tmp_.texture = &all_images_;
}
