#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites_groups/game_scene/grid.h>

void Grid::Draw(Screen& screen) {
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);
    screen.Draw(shape);
}
