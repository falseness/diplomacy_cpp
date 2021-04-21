#include <source/drawable_objects/drawable_object.h>
#include <source/drawable_objects/cell/hexagon.h>
#include <source/options/options.h>
#include <tuple>
#include <source/utility/point.h>
#include <source/player/player.h>

#pragma once

class Cell : public DrawableObject {
    std::pair<int, int> coord_;
    size_t player_index_;
    const std::vector<Player>& players_;
    Hexagon hexagon_;
public:
    Cell(std::pair<int, int>, size_t player_index_, const std::vector<Player>&);
    void Draw(Screen& screen, const GameOptions&);
    std::pair<int, int> get_coord() const;
    Point calculate_pos(const GameOptions& game_options) const;
    const Color& get_color() const;
};
