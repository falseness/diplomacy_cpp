#include <source/drawable_objects/hittable_entity.h>
#include <source/player/entity_stats.h>

#pragma once

class Grid;
class SceneInfo;

class Unit : public HittableEntity {
    int dmg_;
    unsigned int moves_;
protected:
    void Kill() override;
public:
    void NextTurn() override;
    [[nodiscard]] const UnitStats& get_stats() const;
    [[nodiscard]] unsigned int get_speed() const;
    [[nodiscard]] unsigned int get_maximum_hp() const override;
    void Select(SceneInfo&) const override;
    ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    Unit(Cell*, std::string&&);
    void set_cell(Cell*);
    [[nodiscard]] unsigned int get_moves() const;
    void MoveTo(Grid& grid, std::pair<int, int> coord);
    [[nodiscard]] json to_json() override;
    [[nodiscard]] json get_info() const override;
    [[nodiscard]] bool is_passable() const override;
    ~Unit() override = default;
};

class EmptyUnit : public Unit {
public:
    [[nodiscard]] bool is_passable() const override;
    [[nodiscard]] bool is_hittable() const override;
    explicit EmptyUnit(Cell*);
    void Draw(Screen&, const GameOptions&) override;
    void Select(SceneInfo&) const override;
};
