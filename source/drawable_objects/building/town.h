#include "source/drawable_objects/building/building_with_hp.h"
#include "source/drawable_objects/building/barrack.h"

#pragma once

class Grid;

class Town : public Barrack, public BuildingWithHp {
    mutable std::string building_production_plan_;
    // some of this cells may not be suburbs. so we filter them in get_suburbs(). fields is updated in NextTurn method
    std::vector<std::pair<int, int>> potential_suburbs_;
    void set_production_interface_visible(const SceneInfo& scene, bool) const override;
    void UpdateProductionInterface(const SceneInfo& scene) const override;
public:
    [[nodiscard]] std::vector<std::pair<int, int>> get_suburbs(const Grid& grid) const;
    [[nodiscard]] json get_info() const override;
    Town(Cell*, std::string&&, std::vector<std::pair<int, int>>);
    ~Town() override = default;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
    void Select(const SceneInfo&) const override;
    void set_building_production_plan(std::string production_plan) const;
    inline void clear_building_production_plan() const {
        building_production_plan_ = "";
    }
    void AddSuburb(Cell* cell);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) const override;
    void NextTurn() override;
};
