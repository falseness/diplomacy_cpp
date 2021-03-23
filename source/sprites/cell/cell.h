#include <source/sprites/sprite.h>
#include <source/sprites/cell/hexagon.h>
#include <source/options/options.h>
#include <tuple>
#include <source/geometry/point.h>

#ifndef DIPLOMACY_CELL_H
#define DIPLOMACY_CELL_H

class Cell : public Sprite {
    std::pair<int, int> coord_;
    Hexagon* hexagon_;
public:
    Cell(std::pair<int, int>, const GameOptions&);
    ~Cell();
    void Draw(Screen& screen, const GameOptions&);
    std::pair<int, int> get_coord() const;
    Point calculate_pos(const GameOptions& game_options) const ;
};


#endif //DIPLOMACY_CELL_H
