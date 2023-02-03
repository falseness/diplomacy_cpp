#include "entity.h"
#include <source/drawable_objects/cell/cell.h>
#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/player/player.h>

Entity::Entity(Cell* cell_, std::string image_name) : cell_(cell_), image_name_(std::move(image_name)) {}

void Entity::Draw(Screen& screen, const GameOptions& game_options) {
    Vector2D pos = cell_->get_pos(game_options);
    Vector2D offset = game_options.get_image_offset();
    pos.x += offset.x;
    pos.y += offset.y;

    DrawImage(screen, game_options, pos);
}

void Entity::DrawImage(Screen &screen, const GameOptions &game_options,
                       const Vector2D &pos) const {
    screen.DrawOnBuffer(image_name_, game_options.get_image_size(), pos);
    //screen.DrawGridImage(image_name_, game_options.get_image_size(), pos);
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
    return std::move(result);
}

json Entity::get_info() const {
    json result;
    result["name"] = image_name_;
    return std::move(result);
}

void Entity::Select(const SceneInfo& scene) const {
    scene.entity_interface.update(get_info(), get_color());
    scene.entity_interface.set_visible(true);
}

Color Entity::get_color() const {
    return cell_->get_color();
}

Player& Entity::get_player() {
    return cell_->get_player();
}

const Player& Entity::get_player() const {
    return cell_->get_player();
}

bool Entity::is_my_turn() const {
    return cell_->is_my_turn();
}

bool Entity::is_empty() const {
    return image_name_ == Entity::kEmptyEntityName;
}

bool Entity::is_hittable(size_t asking_player_index) const {
    return false;
}

const PlayersEntitiesStats &Entity::get_player_stats() const {
    return cell_->get_player().get_stats();
}

size_t Entity::get_player_index() const {
    return cell_->get_player_index();
}

bool Entity::is_my_player(size_t another_player_index) const {
    return cell_->is_my_player(another_player_index);
}

const std::string Entity::kEmptyEntityName;
