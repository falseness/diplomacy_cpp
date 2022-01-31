#include <source/drawable_objects/building/building_with_hp.h>
#include <source/drawable_objects/building/barrack.h>

#pragma once


class Town : public BuildingWithHp, public Barrack {
    static const std::string kTownImageName;
public:
    json get_info() const override;
    explicit Town(Cell*);
    ~Town() override = default;
};
