#include <source/drawable_objects/drawable_object.h>
#include <source/drawable_objects/cell/hexagon.h>
#include <source/drawable_objects/unit/unit.h>
#include <source/drawable_objects/building/building.h>
#include <source/options/options.h>
#include <tuple>
#include <source/utility/vector2d.h>

class Players;
class Player;

#pragma once

class Cell : public DrawableObject {
    std::pair<int, int> coord_;
    size_t player_index_;
    Players& players_;
    Hexagon hexagon_;
    std::unique_ptr<Unit> unit_;
    std::unique_ptr<Building> building_;
    void set_player(size_t);

public:
    static const float kColorAlphaRatio;
    template <typename UnitType, typename ...Args>
    void CreateUnit(Args&&... args) {
        assert(unit_->is_empty());
        unit_ = std::move(std::make_unique<UnitType>(this, std::forward<Args>(args)...));
        get_player().AddUnit(unit_.get());
    }
    template <typename BuildingType, typename ...Args>
    void CreateBuilding(Args&&... args) {
        assert(building_->is_empty());

        building_ = std::move(static_cast<std::unique_ptr<Building>>(
                std::make_unique<BuildingType>(this, std::forward<Args>(args)...)));
    }
    Cell(std::pair<int, int>, size_t player_index_, Players&);
    void Draw(Screen& screen, const GameOptions&) override;
    [[nodiscard]] std::pair<int, int> get_coord() const;
    [[nodiscard]] Vector2D get_pos(const GameOptions& game_options) const;
    [[nodiscard]] const Color& get_color() const;
    [[nodiscard]] const Player& get_player() const;
    Player& get_player();
    bool IsStore(const Unit*) const;
    Unit* get_unit();
    Building* get_building();
    void set_unit(std::unique_ptr<Unit>&&);
    [[nodiscard]] bool is_my_turn() const;
    [[nodiscard]] bool is_passable() const;
    void MoveUnitTo(Cell&);
};
