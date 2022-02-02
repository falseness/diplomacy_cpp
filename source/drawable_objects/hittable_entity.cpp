//
// Created by nikita on 02.02.2022.
//

#include "hittable_entity.h"

bool HittableEntity::is_hittable() const {
    return !is_my_turn();
}

void HittableEntity::Hit(int dmg) {
    dmg = std::min(dmg, static_cast<int>(hp_));
    hp_ -= dmg;
    if (!hp_)
        Kill();
}

json HittableEntity::get_info() const {
    auto result = Entity::get_info();
    result["info"]["hp"] = std::to_string(hp_) + " / " + std::to_string(get_maximum_hp());
    return result;
}

bool HittableEntity::is_passable() const {
    return is_my_turn();
}
