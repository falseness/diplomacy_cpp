#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites/cell/cell.h>
#include <source/options/options.h>
#include <vector>

#ifndef DIPLOMACY_CPP_GRID_H
#define DIPLOMACY_CPP_GRID_H

class Grid : public SpritesGroup {
    std::vector<std::vector<Cell*>> cells_;
public:
    Grid(const GameOptions&);
    ~Grid();
};

#endif //DIPLOMACY_CPP_GRID_H
