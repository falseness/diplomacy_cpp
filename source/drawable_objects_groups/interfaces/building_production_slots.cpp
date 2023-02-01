#include "building_production_slots.h"
#include "source/drawable_objects/building/town.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/utility/map_additional_functions.h"


bool BuildingProductionSlots::CheckButtonsClick(const Vector2D &pos, SceneInfo &scene,
                                                                         const PlayersEntitiesFactories &factories) {
    auto stat = get_corresponding_stat(pos, factories.buildings_production_stats);
    if (stat == factories.buildings_production_stats.end() || stat->second.cost > town_->get_player().get_gold())
        return false;
    last_click_ = stat->first;

    town_->set_building_production_plan(last_click_);
    factories.buildings_factory.find(last_click_)->second->Select(scene, town_);
    return true;
}

void BuildingProductionSlots::update(const Town *town) {
    town_ = town;
    ProductionSlots::update(town_);
}

BuildingProductionSlots::BuildingProductionSlots(
        Vector2D pos, float background_width, float background_height, const Screen& screen) :
        ProductionSlots(pos, background_width, background_height, screen) {}

void BuildingProductionSlots::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(town_ != nullptr);
    DrawButtonsByStats(screen, game_options, town_->get_player().get_factories_stats().buildings_production_stats);
}

void BuildingProductionSlots::ReClick(SceneInfo& scene) {
    assert(!last_click_.empty());
    assert(town_);
    const auto& factories_stats = town_->get_player().get_factories_stats();
    const auto& stat = safe_find(factories_stats.buildings_production_stats, last_click_);
    if (stat.cost <= town_->get_player().get_gold()) {
        safe_find(factories_stats.buildings_factory, last_click_)->Select(scene, town_);
        return;
    }
    UnSelect(scene);
}

float BuildingProductionSlots::get_bottom() const {
    assert(town_ != nullptr);
    size_t buttons_count = town_->get_player().get_factories_stats().buildings_production_stats.size();
    return button_.get_bottom() + static_cast<float>(buttons_count) * interval_between_.y;
}

void BuildingProductionSlots::UnSelect(SceneInfo& scene) {
    clear_chosen_button();
    town_->clear_building_production_plan();
    town_->Select(scene);
}

void BuildingProductionSlots::set_button_text(
        const std::pair<std::string, EntityProductionStats>& stat) {
    static const std::string kDefaultString = "build";
    static const std::string kSelectedButtonString = "choose";
    if (last_click_.empty()) {
        button_.text.text = kDefaultString;
        return;
    }
    if (should_display_button(stat))
        button_.text.text = kSelectedButtonString;
}

bool BuildingProductionSlots::should_display_button(
        const std::pair<std::string, EntityProductionStats>& stat) const {
    return (last_click_.empty() && stat.second.cost <= town_->get_player().get_gold()) || stat.first == last_click_;
}

bool BuildingProductionSlots::HandleClick(SceneInfo& scene, const Vector2D &click_pos,
                                                                   const GameOptions &game_options) {
    if (!last_click_.empty()) {
        UnSelect(scene);
        return true;
    }
    return ProductionSlots::HandleClick(scene, click_pos, game_options);
}
