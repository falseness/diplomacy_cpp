#include <source/drawable_objects/building/building_with_hp.h>
#include <source/drawable_objects/building/barrack.h>

#pragma once


class Town : public Barrack, public BuildingWithHp {
    static const std::string kTownImageName;
public:
    [[nodiscard]] json get_info() const override;
    explicit Town(Cell*);
    ~Town() override = default;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
};
