#include "entity.h"
#include <source/drawable_objects/cell/cell.h>

Entity::Entity(const Cell* cell_, std::string&& image_name) : cell_(cell_), image_name_(std::move(image_name)) {}

void Entity::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D pos = cell_->get_pos(game_options);
    Vector2D offset = game_options.get_image_offset();
    pos.x += offset.x;
    pos.y += offset.y;
    screen.DrawGridImage(image_name_, game_options.get_image_size(), pos);
}

std::pair<int, int> Entity::get_coord() const {
    return cell_->get_coord();
}

json Entity::to_json() {
    json result;
    result["name"] = image_name_;
    auto coord = get_coord();
    result["coord"]["x"] = coord.first;
    result["coord"]["y"] = coord.second;
    result["hp"] = hp_;
    return std::move(result);
}
