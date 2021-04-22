#include "entity.h"
#include <source/drawable_objects/cell/cell.h>

Entity::Entity(const Cell &cell_, std::string&& image_name) : cell_(cell_), image_name_(std::move(image_name)) {}

void Entity::Draw(Screen& screen, const GameOptions& game_options) {
    Point pos = cell_.calculate_pos(game_options);
    Point offset = game_options.get_image_offset();
    pos.x += offset.x;
    pos.y += offset.y;
    screen.DrawImage(image_name_, game_options.get_image_size(), pos);
}
