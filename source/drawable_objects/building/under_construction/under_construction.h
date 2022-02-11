#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects/cell/cell.h"

#pragma once

template <typename BuildingAfterConstruction>
class BuildingUnderConstruction : public Building {
    ProductionInfo production_info_;
    void DrawImage(Screen &screen, const GameOptions &game_options, const Vector2D &pos) const override;
    static constexpr float kOpacity = 0.5f;
public:
    BuildingUnderConstruction(Cell* cell, std::string image_name, ProductionInfo production_info);
    void NextTurn() override;
    [[nodiscard]] inline bool is_passable() const override;
    void Draw(Screen& screen, const GameOptions& game_options) override;
    [[nodiscard]] json get_info() const override;
};


template<typename BuildingAfterConstruction>
void BuildingUnderConstruction<BuildingAfterConstruction>::NextTurn() {
    assert(production_info_.turns);
    if (--production_info_.turns) {
        Building::NextTurn();
        return;
    }
    cell_->template DestroyBuildingAndCreateOne<BuildingAfterConstruction>(std::string(production_info_.name));
}

template<typename BuildingAfterConstruction>
BuildingUnderConstruction<BuildingAfterConstruction>::BuildingUnderConstruction(
        Cell *cell, std::string image_name, ProductionInfo production_info) :
        Building(cell, image_name), Entity(cell, std::move(image_name)), production_info_(std::move(production_info)) {

}

template<typename BuildingAfterConstruction>
void BuildingUnderConstruction<BuildingAfterConstruction>::Draw(Screen &screen, const GameOptions &game_options) {
    Building::Draw(screen, game_options);
}

template<typename BuildingAfterConstruction>
void BuildingUnderConstruction<BuildingAfterConstruction>::DrawImage(Screen &screen, const GameOptions &game_options,
                                                                     const Vector2D &pos) const {
    screen.DrawGridImageWithOpactiy(image_name_, game_options.get_image_size(), pos, kOpacity);
}

template<typename BuildingAfterConstruction>
bool BuildingUnderConstruction<BuildingAfterConstruction>::is_passable() const {
    return true;
}

template<typename BuildingAfterConstruction>
json BuildingUnderConstruction<BuildingAfterConstruction>::get_info() const {
    auto result = Entity::get_info();
    result["info"]["turns"] = production_info_.turns;
    return result;
}
