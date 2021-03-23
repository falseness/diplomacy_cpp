#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>
class Cell;

#ifndef DIPLOMACY_HEXAGON_H
#define DIPLOMACY_HEXAGON_H

class Hexagon : public Sprite {
    const Cell& cell_;
    sf::CircleShape* hexagon_;
public:
    Hexagon(const Cell&, float, float, sf::Color, sf::Color, float);
    ~Hexagon();
    void Draw(Screen&, const GameOptions&);
};

#endif //DIPLOMACY_HEXAGON_H
