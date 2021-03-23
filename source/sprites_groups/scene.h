#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#ifndef DIPLOMACY_CPP_SCENE_H
#define DIPLOMACY_CPP_SCENE_H

class Scene : public SpritesGroup {
public:
    virtual void LoopIteration(Screen&, const GameOptions&);
};

#endif //DIPLOMACY_CPP_SCENE_H
