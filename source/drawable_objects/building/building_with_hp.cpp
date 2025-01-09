#include "building_with_hp.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"


BuildingWithHp::BuildingWithHp(Cell *cell, std::string image_name) :
    Building(cell, std::string(image_name)), Entity(cell, std::move(image_name)) {
    hp_ = get_stats().hp;
}

const BuildingWithHpStats& BuildingWithHp::get_stats() const {
    return cell_->get_player().get_stats().buildings_with_hp.find(image_name_)->second;
}

unsigned int BuildingWithHp::get_maximum_hp() const {
    return get_stats().hp;
}

void BuildingWithHp::AskGridToDecreaseHP(int dmg, Grid &grid) const {
    grid.DecreaseBuildingHP(get_coord(), dmg);
}

json BuildingWithHp::get_info() const {
    auto result = Building::get_info();
    result["info"]["hp"] = HittableEntity::get_info()["info"]["hp"];
    return result;
}

void BuildingWithHp::DrawHPBar(Screen &screen, const GameOptions &game_options) const {
    const float building_hp_bar_y_offset = game_options.hexagon_options.radius * 0.5;
    HittableEntity::DrawHPBar(building_hp_bar_y_offset, screen, game_options);
}

void BuildingWithHp::Draw(Screen &screen, const GameOptions &game_options) {
    Building::Draw(screen, game_options);
    DrawHPBar(screen, game_options);
}
