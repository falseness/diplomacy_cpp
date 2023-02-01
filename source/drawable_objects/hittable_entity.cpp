//
// Created by nikita on 02.02.2022.
//

#include "hittable_entity.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"

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
