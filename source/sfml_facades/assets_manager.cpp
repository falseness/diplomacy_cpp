 #include "assets_manager.h"

void AssetsManager::load_all_images() {
    images_["peasant"] = sf::Texture();
    images_["peasant"].loadFromFile("entities/units/peasant.png");

    images_["archer"] = sf::Texture();
    images_["archer"].loadFromFile("entities/units/archer.png");

    load_image("swordsman", "entities/units/swordsman.png");
    load_image("cavalry", "entities/units/cavalry.png");

    load_image("catapult", "entities/units/catapult.png");

    images_["town"] = sf::Texture();
    images_["town"].loadFromFile("entities/buildings/town.png");
    images_["barrack"] = sf::Texture();
    images_["barrack"].loadFromFile("entities/buildings/barrack.png");
    images_["farm"] = sf::Texture();
    images_["farm"].loadFromFile("entities/buildings/farm.png");

    load_image("wall", "entities/buildings/wall.png");
    load_image("tower", "entities/buildings/tower.png");

    images_["gold"] = sf::Texture();
    images_["gold"].loadFromFile("other_images/gold.png");
    images_["debug"] = sf::Texture();
    images_["debug"].loadFromFile("entities/debug_image.png");
    images_["suburb"] = sf::Texture();
    images_["suburb"].loadFromFile("other_images/suburb.png");

    load_image("mountain", "entities/buildings/mountain.png");
    load_image("lake", "entities/buildings/lake.png");
    load_image("sea", "entities/buildings/sea.png");
}

void AssetsManager::load_image(const std::string& name, const std::string& path) {
    images_[name] = sf::Texture();
    images_[name].loadFromFile(path);
}

void AssetsManager::load_all_fonts() {
    fonts_["times new roman"] = sf::Font();
    fonts_["times new roman"].loadFromFile("fonts/times_new_roman.ttf");
}

AssetsManager::AssetsManager() {
    load_all_fonts();
    load_all_images();

}




