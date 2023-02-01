#include "source/drawable_objects/building/building_with_hp.h"
#include "source/drawable_objects/building/barrack.h"

#pragma once

class Grid;

class Town : public Barrack, public BuildingWithHp {
    static const int kTownRangeAddition = 1;

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
    [[nodiscard]] bool is_passable(size_t asking_player_index) const override;
    [[nodiscard]] bool is_hittable(size_t asking_player_index) const override;
    void Select(const SceneInfo&) const override;
    void set_building_production_plan(std::string production_plan) const;
    inline void clear_building_production_plan() const {
        building_production_plan_ = "";
    }
    void AddSuburb(Cell* cell);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) const override;
    void NextTurn(SceneInfo& scene) override;
    [[nodiscard]] inline bool can_be_shot_through() const override {
        return false;
    }
    [[nodiscard]] inline bool is_high_ground() const override {
        return true;
    }
    [[nodiscard]] inline int get_range_addition() const override {
        return kTownRangeAddition;
    }
    void Kill(Grid& grid) const override;
    [[nodiscard]] inline bool should_be_destroyed_after_town_destroying() const {
        assert(false);
        return false;
    }
};
