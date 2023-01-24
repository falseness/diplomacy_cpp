#include "town_production.h"
#include "source/drawable_objects/building/town.h"

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
    UpdateSlotsVisibility();
    drawable_objects_.push_back(&unit_and_building_switch_);
    drawable_objects_.push_back(&building_slots_);
}

void TownProductionInterface::update(const Town* town) {
    UpdateSlotsVisibility();
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
        UpdateSlotsVisibility();
        return true;
    }
    if (building_slots_.HandleClick(scene, click_pos, game_options))
        return true;
    building_slots_.UnSelect(scene);

    return ProductionInterface::HandleClick(scene, click_pos, game_options);
}

void TownProductionInterface::UpdateSlotsVisibility() {
    production_slots_->set_visible(unit_and_building_switch_.is_left_selected);
    building_slots_.set_visible(!unit_and_building_switch_.is_left_selected);
}

void TownProductionInterface::ReClick(SceneInfo& scene) {
    building_slots_.ReClick(scene);
}

void TownProductionInterface::UpdateSize() {
    background_.height = std::max(building_slots_.get_bottom(), production_slots_->get_bottom()) -
            background_.up_side_y;
}

void TownProductionInterface::set_visible(bool visibility) {
    if (!visibility)
        building_slots_.clear_chosen_button();
    DrawableObjectsGroup::set_visible(visibility);
}
