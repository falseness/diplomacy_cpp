#pragma once

#include <set>

#include "source/drawable_objects/building/building_with_hp.h"
#include "source/drawable_objects/building/barrack.h"



class Grid;

class Town : public Barrack, public BuildingWithHp {
    static const int kTownRangeAddition = 1;
    static const int kSuburbsIncome = 1;

    mutable std::string building_production_plan_;
    // some of this cells may not be suburbs. so we filter them in get_suburbs(). fields is updated in NextTurn method
    std::set<std::pair<int, int>> suburbs_;
    void set_production_interface_visible(const SceneInfo& scene, bool) const override;
    void UpdateProductionInterface(const SceneInfo& scene) const override;
public:
    [[nodiscard]] json get_info() const override;
    Town(Cell*, std::string&&, std::set<std::pair<int, int>> suburbs);
    ~Town() override = default;
    [[nodiscard]] bool is_passable(size_t asking_player_index) const override;
    [[nodiscard]] bool is_hittable(size_t asking_player_index) const override;
    void Select(const SceneInfo&) const override;
    void set_building_production_plan(std::string production_plan) const;
    inline void clear_building_production_plan() const {
        building_production_plan_ = "";
    }
    void AddSuburb(Cell* cell);
    void DeleteSuburb(Cell* cell);
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
    [[nodiscard]] inline bool should_be_destroyed_after_town_destroying() const override {
        assert(false);
        return false;
    }
    [[nodiscard]] inline int get_income() const override {
        // todo: fix potential suburbs
        return SuburbBuilding::get_income() + kSuburbsIncome * static_cast<int>(suburbs_.size());
    }
    [[nodiscard]] inline bool contains_suburb(std::pair<int, int> suburb_coord) const {
        return suburbs_.contains(suburb_coord);
    }
    [[nodiscard]] inline std::set<std::pair<int, int>> get_suburbs() const {
        return suburbs_;
    }
};
