#include <source/drawable_objects/entity.h>
#include <source/player/entity_stats.h>

#pragma once

class Grid;
class SceneInfo;

class Unit : public Entity {
    int dmg_;
    unsigned int moves_;
public:
    const UnitStats& get_unit_type_stats() const;
    unsigned int get_speed() const;
    unsigned int get_maximum_hp() const;
    void Select(SceneInfo&);
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    Unit(const Cell*, std::string&&);
    void set_cell(const Cell*);
    unsigned int get_moves() const;
    void MoveTo(Grid& grid, std::pair<int, int> coord);
    virtual json to_json() override;
    virtual json get_info() override;
};
