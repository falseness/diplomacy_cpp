#include "hittable_entity.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/interface_elements/rounded_rectangle.h"
#include "source/drawable_objects/entity_bar.h"


bool HittableEntity::is_hittable(size_t asking_player_index) const {
    return !is_my_player(asking_player_index);
}

void HittableEntity::Hit(int dmg, Grid& grid) const {
    dmg = std::min(dmg, static_cast<int>(hp_));
    AskGridToDecreaseHP(dmg, grid);
    if (!hp_)
        Kill(grid);
}

json HittableEntity::get_info() const {
    auto result = Entity::get_info();
    result["info"]["hp"] = std::to_string(hp_) + " / " + std::to_string(get_maximum_hp());
    return result;
}

bool HittableEntity::is_passable(size_t asking_player_index) const {
    return is_my_player(asking_player_index);
}

void HittableEntity::DecreaseHP(int dmg) {
    assert(static_cast<int>(hp_) >= dmg);
    hp_ -= dmg;
}

void HittableEntity::DrawHPBar(float y_offset, Screen& screen, const GameOptions& game_options) const {
    static constexpr Color kHPPresenceColor(43, 181, 43);
    static constexpr Color kHPAbsenseColor(179, 179, 179);

    static constexpr float kSideRadiusRatio = 0.15;
    DrawEntityBar(
            hp_, get_maximum_hp(), get_image_pos(game_options) + Vector2D(0, y_offset),
                  Vector2D(kSideRadiusRatio, kSideRadiusRatio),
                  kHPPresenceColor, kHPAbsenseColor, RectangleBuffer::HP, screen, game_options);
}
