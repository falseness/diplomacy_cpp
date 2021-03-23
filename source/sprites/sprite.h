#include <source/sfml_facades/screen.h>

#ifndef DIPLOMACY_CPP_SPRITES_H
#define DIPLOMACY_CPP_SPRITES_H
class Sprite {
public:
    //virtual void HandleEvent(const sf::Event&) = 0;
    virtual void Draw(Screen& screen) = 0;
};
#endif //DIPLOMACY_CPP_SPRITES_H
