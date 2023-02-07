#include "source/drawable_objects/entity.h"

#include "source/player/entity_stats.h"

#pragma once

class BuildingStats;

class Building : public virtual Entity {
    [[nodiscard]] const BuildingStats& get_stats() const;
public:
    Building(Cell* cell, std::string image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) const override;
    void NextTurn(SceneInfo& scene) override;
    void Select(const SceneInfo&) const override;
    [[nodiscard]] virtual inline bool can_be_shot_through() const {
        return true;
    }
    [[nodiscard]] virtual inline int get_range_addition() const {
        return 0;
    }
    [[nodiscard]] virtual inline bool can_be_shot(size_t asking_player_index) const {
        return !is_my_player(asking_player_index);
    }
    [[nodiscard]] virtual inline bool is_high_ground() const {
        return false;
    }
    [[nodiscard]] bool should_be_destroyed_after_town_destroying() const {
        return get_stats().should_be_destroyed_after_town_destroying;
    }
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] virtual inline std::string get_additional_text_info() const {
        return "";
    }
    void Kill(Grid& grid) const override;
    ~Building() override;
};

class EmptyBuilding : public Building {
public:
    [[nodiscard]] inline bool can_be_shot(size_t asking_player_index) const override {
        return false;
    }
    [[nodiscard]] bool is_passable(size_t asking_player_index) const override;
    explicit EmptyBuilding(Cell*);
    void Draw(Screen&, const GameOptions&) override;
};
