#include <string>
#include <source/drawable_objects/drawable_object.h>
#include <nlohmann/json.hpp>
#include <source/player/player.h>

using json = nlohmann::json;

#pragma once

class Cell;
class SceneInfo;

struct ClickResponse {
    bool should_remove_selection;
    bool should_reclick;
    bool should_change_selection_to_building_on_same_cell;
};

class Entity : public DrawableObject {
protected:
    Cell* cell_;
public:
    const std::string image_name_;
    virtual void Draw(Screen&, const GameOptions&) override;
    virtual ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) = 0;
    Entity(Cell*, std::string&&);
    [[nodiscard]] std::pair<int, int> get_coord() const;
    virtual json to_json();
    virtual json get_info() const;
    virtual void Select(SceneInfo&);
    [[nodiscard]] Color get_color() const;
    virtual void NextTurn() = 0;
    Player& get_player();
    const Player& get_player() const;
    ~Entity() override = default;
};


