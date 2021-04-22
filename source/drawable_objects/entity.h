#include <string>
#include <source/drawable_objects/drawable_object.h>

#pragma once

class Cell;

class Entity : public DrawableObject {
protected:
    const Cell& cell_;
    unsigned int hp_;
public:
    const std::string image_name_;
    virtual void Draw(Screen&, const GameOptions&) override;
    Entity(const Cell& cell_, std::string&&);
};