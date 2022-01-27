#include <string>
#include <source/drawable_objects/drawable_object.h>

#pragma once

class Cell;
class Grid;

class Entity : public DrawableObject {
protected:
    const Cell* cell_;
    unsigned int hp_;
public:
    const std::string image_name_;
    virtual void Draw(Screen&, const GameOptions&) override;
    virtual bool HandleClick(Grid*, const Vector2D& click_pos, const GameOptions& game_options) = 0;
    Entity(const Cell*, std::string&&);
    std::pair<int, int> get_coord() const;

};
