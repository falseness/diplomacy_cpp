#include "barrack.h"

Barrack::Barrack(const Cell *cell, std::string &&image_name) :
    SuburbBuilding(cell, std::string(image_name)), Building(cell, std::string(image_name)) {}
