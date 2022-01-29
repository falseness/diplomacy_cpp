#include <source/drawable_objects/building/building_with_hp.h>
#include <source/drawable_objects/building/suburb_building.h>

#pragma once


class Town : public BuildingWithHp, public SuburbBuilding {
    static const std::string kTownImageName;
public:
    Town(const Cell*);
    ~Town() override = default;
};
