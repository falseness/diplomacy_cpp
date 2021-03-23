#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>
#include <vector>

#ifndef DIPLOMACY_CPP_SPRITES_GROUP_H
#define DIPLOMACY_CPP_SPRITES_GROUP_H

class SpritesGroup : public Sprite {
protected:
    std::vector<Sprite*> sprites_;
public:
    virtual void Draw(Screen& screen, const GameOptions&);
    //void HandleEvent() {}
    ~SpritesGroup();
};

#endif //DIPLOMACY_CPP_SPRITES_GROUP_H
