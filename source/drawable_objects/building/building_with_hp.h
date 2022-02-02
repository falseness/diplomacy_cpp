#include <source/drawable_objects/building/building.h>
#include <source/drawable_objects/hittable_entity.h>

#pragma once

class BuildingWithHpStats;

class BuildingWithHp : virtual public Building, public HittableEntity {
protected:
    void Kill() override;
public:
    [[nodiscard]] const BuildingWithHpStats& get_stats() const;
    BuildingWithHp(Cell* cell, std::string&& image_name);
    ~BuildingWithHp() override = default;
    [[nodiscard]] unsigned int get_maximum_hp() const override;
};
