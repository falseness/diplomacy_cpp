#include "source/drawable_objects/drawable_object.h"
#include "source/drawable_objects/cell/hexagon.h"
#include "source/drawable_objects/unit/unit.h"
#include "source/drawable_objects/building/building.h"
#include "source/drawable_objects/building/suburb_building.h"
#include "source/options/game.h"
#include <tuple>
#include "source/utility/vector2d.h"
#include "source/utility/segment.h"
#include "source/player/player.h"

#pragma once

class Players;
#include <iostream>


class Cell : public DrawableObject {
    friend Grid;
    size_t player_index_;
    Players& players_;
    Hexagon hexagon_;
    std::unique_ptr<Unit> unit_;
    std::unique_ptr<Building> building_;
    bool is_suburb_;
    std::pair<int, int> coord_;
public:
    void set_player(size_t);
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
    template <typename BuildingType, typename ...Args>
    void DestroyBuildingAndCreateOne(Args&&... args) {
        assert(!building_->is_empty());

        DeleteBuilding();

        building_ = std::move(static_cast<std::unique_ptr<Building>>(
                          std::make_unique<BuildingType>(this, std::forward<Args>(args)...)));
    }
    Cell(std::pair<int, int>, size_t player_index_, Players&, bool is_suburb = false);
    void Draw(Screen& screen, const GameOptions&) override;
    [[nodiscard]] std::pair<int, int> get_coord() const;
    [[nodiscard]] Vector2D get_pos(const GameOptions& game_options) const;
    [[nodiscard]] const Color& get_color() const;
    [[nodiscard]] const Player& get_player() const;
    Player& get_player();
    bool IsStore(const Unit*) const;
    [[nodiscard]] const Unit* get_unit() const {
        return unit_.get();
    }
    [[nodiscard]] const Building* get_building() const {
        return building_.get();
    }
    void set_unit(std::unique_ptr<Unit>&&);
    [[nodiscard]] bool is_my_turn() const;
    [[nodiscard]] bool is_passable() const;
    [[nodiscard]] bool is_hittable() const;
    [[nodiscard]] bool is_suburb() const;
    void set_suburb(bool suburb_state);
    void DeleteUnit();
    void DeleteBuilding();
    void MoveUnitTo(const Cell &destination, Grid &grid) const;
    void MoveUnitTo(Cell& destination);
    void HitSomethingOnCell(int dmg, Grid&) const;
    Segment get_side(uint8_t, Screen&, const GameOptions&) const;
private:
    [[nodiscard]] inline Unit* get_unit_ptr() {
        return unit_.get();
    }
    [[nodiscard]] inline Building* get_building_ptr() {
        return building_.get();
    }
};
