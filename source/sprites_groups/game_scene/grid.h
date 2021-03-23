#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>

#ifndef DIPLOMACY_CPP_GRID_H
#define DIPLOMACY_CPP_GRID_H

class Grid : public SpritesGroup {
    void Draw(Screen& screen);
};

#endif //DIPLOMACY_CPP_GRID_H
