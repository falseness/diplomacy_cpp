#include "barrack.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <cassert>

Barrack::Barrack(Cell *cell, std::string &&image_name) :
    SuburbBuilding(cell, std::string(image_name)), Building(cell, std::string(image_name)) {}

ClickResponse Barrack::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions& game_options) {
    auto result = Building::HandleClick(scene, pos, game_options);
    if (result.should_remove_selection)
        scene.production_interface.set_visible(false);
    return result;
}

void Barrack::Select(SceneInfo& scene) {
    scene.production_interface.update(this);
    scene.production_interface.set_visible(true);
    Entity::Select(scene);
}

void Barrack::NextTurn() {
    if (!production_in_progress_)
        return;
    const auto& factories = get_player().get_factories_stats();
    const auto& factory = *factories.units_factory.find(production_.unit_name)->second;
    factory.NextTurn(get_player(), production_);
    if (!get_turns_left() && cell_->get_unit() == nullptr) {
        factory.CreateUnit(cell_, production_);
        production_in_progress_ = false;
    }
}

void Barrack::StartProduction(ProductionInfo production) {
    assert(!production_in_progress_);
    production_in_progress_ = true;
    production_ = std::move(production);
}

bool Barrack::is_production_in_progress() const {
    return production_in_progress_;
}

json Barrack::get_info() const
{
    auto result = SuburbBuilding::get_info();
    if (production_in_progress_) {
        result["info"]["training"] = production_.unit_name;
        result["info"]["turns"] = get_turns_left();
    }
    return result;
}

unsigned int Barrack::get_turns_left() const {
    assert(production_in_progress_);
    const auto& factories = get_player().get_factories_stats();
    const auto& factory = *factories.units_factory.find(production_.unit_name)->second;
    return factory.get_turns_left(get_player(), production_);
}
