#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>
#include <vector>
#include <source/utility/all_usings.h>

#pragma once

class SpritesGroup : public Sprite {
protected:
    std::vector<Sprite*> sprites_;
public:
    virtual void Draw(Screen& screen, const GameOptions&);
    //void HandleEvent() {}
};
