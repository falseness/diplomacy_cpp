#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>

#ifndef DIPLOMACY_CPP_SCENE_H
#define DIPLOMACY_CPP_SCENE_H

class Scene : public SpritesGroup {
public:
    virtual void LoopIteration(Screen& screen);
};

#endif //DIPLOMACY_CPP_SCENE_H
