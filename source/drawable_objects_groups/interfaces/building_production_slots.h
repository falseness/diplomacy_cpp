#include "source/drawable_objects_groups/interfaces/production_slots.h"

#pragma once

class BuildingProductionSlots : public ProductionSlots {
    std::string last_click_;
    Town* town_ = nullptr;
    bool CheckButtonsClick(const Vector2D& pos, SceneInfo& scene,
                           const PlayersEntitiesFactories& factories) override;
    void set_button_text(const std::pair<std::string, EntityProductionStats>& stat) override;
    [[nodiscard]] bool should_display_button(
            const std::pair<std::string, EntityProductionStats>& stat) const override;
public:
    void Draw(Screen& screen, const GameOptions&) override;
    BuildingProductionSlots(Vector2D pos, float background_width, float background_height, const Screen&);
    void update(Town* town);
    void ReClick(SceneInfo& scene);
    void UnSelect(SceneInfo&);
    inline void clear_chosen_button() {
        last_click_ = "";
    }
    [[nodiscard]] float get_bottom() const override;
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    [[nodiscard]] inline bool can_start_new_production() const override {
        return true;
    }
};
