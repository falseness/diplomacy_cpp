#include <source/drawable_objects/entity.h>
#include <source/player/entity_stats.h>
#pragma once

class Unit : public Entity {
    int dmg_;
    unsigned int moves_;
public:
    const UnitStats& get_unit_type_stats() const;
    void Select(Grid*);
    bool HandleClick(Grid*, const Vector2D& click_pos, const GameOptions& game_options) override;
    Unit(const Cell*, std::string&&);
    void set_cell(const Cell*);
    unsigned int get_moves() const;
    void MoveTo(Grid* grid, std::pair<int, int> coord);
};
