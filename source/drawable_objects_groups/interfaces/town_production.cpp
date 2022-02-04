#include "town_production.h"
#include <source/drawable_objects/building/town.h>

TownProductionInterface::TownProductionInterface(const Screen &screen) : ProductionInterface(screen) {
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
    drawable_objects_.push_back(&unit_and_building_switch_);
}

void TownProductionInterface::update(Town* town) {
    unit_and_building_switch_.get_selected_text().color = town->get_color();
    ProductionInterface::update(town);
}

void TownProductionInterface::Draw(Screen& screen, const GameOptions& game_options) {
    ProductionInterface::Draw(screen, game_options);

}
