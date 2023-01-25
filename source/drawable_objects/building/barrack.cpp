#include "barrack.h"
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects/cell/cell.h>
#include <cassert>

Barrack::Barrack(Cell *cell, std::string image_name) :
    SuburbBuilding(cell, image_name), Building(cell, image_name),
    Entity(cell, std::move(image_name)) {}

ClickResponse Barrack::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions& game_options) const {
    auto result = Building::HandleClick(scene, pos, game_options);
    if (result.should_remove_selection)
        set_production_interface_visible(scene, false);
    return result;
}

void Barrack::Select(const SceneInfo& scene) const {
    SelectionProductionInterface(scene);
    Building::Select(scene);
}

void Barrack::NextTurn() {
    if (!production_in_progress_)
        return;
    const auto& factories = get_player().get_factories_stats();
    const auto& factory = *factories.units_factory.find(production_.name)->second;
    factory.NextTurn(get_player(), production_);
    if (!get_turns_left() && cell_->get_unit()->is_empty()) {
        factory.Create(cell_, production_);
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
        result["info"]["training"] = production_.name;
        result["info"]["turns"] = get_turns_left();
    }
    return result;
}

unsigned int Barrack::get_turns_left() const {
    assert(is_production_in_progress());
    const auto& factories = get_player().get_factories_stats();
    const auto& factory = *factories.units_factory.find(production_.name)->second;
    return factory.get_turns_left(get_player(), production_);
}

std::string Barrack::get_training_unit_name() const {
    assert(is_production_in_progress());
    return production_.name;
}

void Barrack::set_production_interface_visible(const SceneInfo &scene, bool visibility) const {
    scene.production_interface.set_visible(visibility);
}

void Barrack::UpdateProductionInterface(const SceneInfo &scene) const {
    scene.production_interface.update(this);
}

void Barrack::SelectionProductionInterface(const SceneInfo &scene) const {
    if (is_my_turn()) {
        set_production_interface_visible(scene, true);
        UpdateProductionInterface(scene);
    }
}
