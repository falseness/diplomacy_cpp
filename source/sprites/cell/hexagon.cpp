#include <source/sprites/cell/hexagon.h>
#include <source/options/options.h>
#include <source/sprites/cell/cell.h>

Hexagon::Hexagon(const Cell& cell, float radius, float angle, sf::Color fill_color, sf::Color outline_color,
                 float outline_thickness) : cell_(cell), hexagon_(new sf::CircleShape(radius, 6)) {
    hexagon_->setFillColor(fill_color);
    hexagon_->setOutlineColor(outline_color);
    hexagon_->setOutlineThickness(outline_thickness);
    hexagon_->setRotation(angle);
}
Hexagon::~Hexagon() {
    delete hexagon_;
}

void Hexagon::Draw(Screen& screen, const GameOptions& game_options) {
    Point position = cell_.calculate_pos(game_options);
    hexagon_->setPosition(position.x, position.y);
    screen.Draw(*hexagon_);
}
