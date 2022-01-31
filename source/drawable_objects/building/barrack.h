#include <source/drawable_objects/building/suburb_building.h>

#pragma once

class Barrack : virtual public SuburbBuilding {
public:
    Barrack(Cell* cell, std::string&& image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void Select(SceneInfo&) override;
};