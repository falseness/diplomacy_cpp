#include <source/drawable_objects/entity.h>
#include <source/player/entity_stats.h>

#pragma once

class Grid;
class SceneInfo;

class Unit : public Entity {
    unsigned int hp_;
    int dmg_;
    unsigned int moves_;
public:
    void NextTurn();
    [[nodiscard]] const UnitStats& get_stats() const;
    [[nodiscard]] unsigned int get_speed() const;
    [[nodiscard]] unsigned int get_maximum_hp() const;
    void Select(SceneInfo&) override;
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    Unit(Cell*, std::string&&);
    void set_cell(Cell*);
    [[nodiscard]] unsigned int get_moves() const;
    void MoveTo(Grid& grid, std::pair<int, int> coord);
    virtual json to_json() override;
    virtual json get_info() const override;
    ~Unit() override = default;
};
