#include <source/drawable_objects/drawable_object.h>
#include <source/drawable_objects/cell/hexagon.h>
#include <source/options/options.h>
#include <tuple>
#include <source/utility/point.h>

#pragma once

class Cell : public DrawableObject {
    std::pair<int, int> coord_;
    Hexagon hexagon_;
public:
    Cell(std::pair<int, int>, const GameOptions&);
    void Draw(Screen& screen, const GameOptions&);
    std::pair<int, int> get_coord() const;
    Point calculate_pos(const GameOptions& game_options) const;
};
