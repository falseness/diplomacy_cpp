#include <source/drawable_objects/entity.h>

#pragma once

class Grid;


class HittableEntity : virtual public Entity {
protected:
    unsigned int hp_;
    virtual void AskGridToDecreaseHP(int dmg, Grid& grid) const = 0;
public:
    virtual void Hit(int, Grid& grid) const;
    // dmg may be negative. it is ok.

    void DecreaseHP(int);
    [[nodiscard]] virtual unsigned int get_maximum_hp() const = 0;
    [[nodiscard]] bool is_hittable(size_t asking_player_index) const override;
    [[nodiscard]] bool is_passable(size_t asking_player_index) const override;
    [[nodiscard]] json get_info() const override;
};
