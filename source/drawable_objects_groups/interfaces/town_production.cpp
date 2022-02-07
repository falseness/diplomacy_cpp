#include "town_production.h"
#include <source/drawable_objects/building/town.h>

TownProductionInterface::TownProductionInterface(const Screen &screen) : ProductionInterface(screen),
        building_slots_(get_slots_pos(screen), this_width, this_height, screen) {

    unit_and_building_switch_.left_text.text = "units";
    unit_and_building_switch_.right_text.text = "buildings";

    unit_and_building_switch_.right_text.color = ProductionSlots::kButtonTextColor;
    unit_and_building_switch_.background_color = ProductionSlots::kButtonBackgroundColor;
    unit_and_building_switch_.set_text_size(ProductionSlots::get_button_text_size(screen));

    unit_and_building_switch_.corner_radius = ProductionSlots::get_button_corner_radius(screen);
    unit_and_building_switch_.border_width = ProductionSlots::get_button_border_width(screen);

    unit_and_building_switch_.width = get_width() * 0.6f;
    unit_and_building_switch_.set_center_x(get_center_x());
    unit_and_building_switch_.height = get_margin_between_gold_image_and_slots(screen) * 0.5f;
    unit_and_building_switch_.set_center_y(gold_image_.position.y + gold_image_.size.height);
    update_slots_visibility();
    drawable_objects_.push_back(&unit_and_building_switch_);
    drawable_objects_.push_back(&building_slots_);
}

void TownProductionInterface::update(Town* town) {
    update_slots_visibility();
    unit_and_building_switch_.get_selected_text().color = town->get_color();
    building_slots_.update(town);
    ProductionInterface::update(town);
}

void TownProductionInterface::Draw(Screen& screen, const GameOptions& game_options) {
    ProductionInterface::Draw(screen, game_options);

}

bool TownProductionInterface::HandleClick(SceneInfo& scene, const Vector2D &click_pos,
                                          const GameOptions &game_options) {
    if (!visible_ || !background_.is_inside(click_pos))
        return false;
    if (unit_and_building_switch_.is_inside(click_pos)) {
        unit_and_building_switch_.do_switch();
        update_slots_visibility();
        return true;
    }
    if (building_slots_.HandleClick(scene, click_pos, game_options))
        return true;

    return ProductionInterface::HandleClick(scene, click_pos, game_options);
}

void TownProductionInterface::update_slots_visibility() {
    production_slots_->set_visible(unit_and_building_switch_.is_left_selected);
    building_slots_.set_visible(!unit_and_building_switch_.is_left_selected);
}

void TownProductionInterface::ReClick(SceneInfo& scene) {
    building_slots_.ReClick(scene);
}

bool TownProductionInterface::BuildingProductionSlots::CheckButtonsClick(const Vector2D &pos, SceneInfo &scene,
                                                                         const PlayersEntitiesFactories &factories) {
    auto stat = get_corresponding_stat(pos, factories.buildings_production_stats);
    if (stat == factories.buildings_production_stats.end())
        return false;
    last_click_ = stat->first;
    town_->set_building_production_plan(last_click_);
    factories.buildings_factory.find(last_click_)->second->Select(scene, town_);
    return true;
}

void TownProductionInterface::BuildingProductionSlots::update(Town *town) {
    town_ = town;
    ProductionSlots::update(town_);
}

TownProductionInterface::BuildingProductionSlots::BuildingProductionSlots(
        Vector2D pos, float background_width, float background_height, const Screen& screen) :
        ProductionSlots(pos, background_width, background_height, screen) {}

void TownProductionInterface::BuildingProductionSlots::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(town_ != nullptr);
    DrawButtonsByStats(screen, game_options, town_->get_player().get_factories_stats().buildings_production_stats);
}

void TownProductionInterface::BuildingProductionSlots::ReClick(SceneInfo& scene) {
    assert(!last_click_.empty());
    town_->get_player().get_factories_stats().buildings_factory.find(last_click_)->second->Select(scene, town_);
}
