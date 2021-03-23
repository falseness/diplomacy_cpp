#include <source/sfml_facades/screen.h>
#include <source/options/options.h>

#ifndef DIPLOMACY_CPP_SPRITES_H
#define DIPLOMACY_CPP_SPRITES_H
class Sprite {
public:
    //virtual void HandleEvent(const sf::Event&) = 0;
    virtual void Draw(Screen&, const GameOptions&) = 0;
};
#endif //DIPLOMACY_CPP_SPRITES_H
