#include <source/drawable_objects/drawable_object.h>
#include <source/drawable_objects/cell/hexagon.h>
#include <source/drawable_objects/unit/unit.h>
#include <source/options/options.h>
#include <tuple>
#include <source/utility/vector2d.h>
#include <source/player/player.h>

#pragma once

class Cell : public DrawableObject {
    std::pair<int, int> coord_;
    size_t player_index_;
    const std::vector<Player>& players_;
    Hexagon hexagon_;
    std::unique_ptr<Unit> unit_;
public:
    template <typename UnitType, typename ...Args>
    void CreateUnit(Args&&... args) {
        if (unit_ != nullptr)
            throw std::out_of_range("unit in cell is not nullptr");
        unit_ = std::move(std::make_unique<UnitType>(this, std::forward<Args>(args)...));
    }
    Cell(std::pair<int, int>, size_t player_index_, const std::vector<Player>&);
    void Draw(Screen& screen, const GameOptions&);
    std::pair<int, int> get_coord() const;
    Vector2D get_pos(const GameOptions& game_options) const;
    const Color& get_color() const;
    const Player& get_player() const;
    bool IsStore(const Unit*) const;
    Unit* get_unit();
    void set_unit(std::unique_ptr<Unit>&&);
    void MoveUnitTo(Cell&);
};
