#include <source/drawable_objects/entity.h>

#pragma once

class HittableEntity : virtual public Entity {
protected:
    unsigned int hp_;
    virtual void Kill() = 0;
public:
    virtual void Hit(int);
    [[nodiscard]] virtual unsigned int get_maximum_hp() const = 0;
    [[nodiscard]] bool is_hittable() const override;
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] json get_info() const override;
};
