#include <source/drawable_objects/building/building_with_hp.h>
#include <source/drawable_objects/building/barrack.h>

#pragma once


class Town : public Barrack, public BuildingWithHp {
    std::vector<std::pair<int, int>> suburbs_;
    void set_production_interface_visible(SceneInfo& scene, bool) const override;
    void update_production_interface(SceneInfo& scene) override;
public:
    [[nodiscard]] json get_info() const override;
    Town(Cell*, std::string&&, std::vector<std::pair<int, int>>&&);
    ~Town() override = default;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
};
