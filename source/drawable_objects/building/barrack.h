#include <source/drawable_objects/building/suburb_building.h>

#pragma once

class Barrack : virtual public SuburbBuilding {
public:
    Barrack(const Cell* cell, std::string&& image_name);
};