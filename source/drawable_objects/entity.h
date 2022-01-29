#include <string>
#include <source/drawable_objects/drawable_object.h>
#include <nlohmann/json.hpp>

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
    const Cell* cell_;
public:
    const std::string image_name_;
    virtual void Draw(Screen&, const GameOptions&) override;
    virtual ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) = 0;
    Entity(const Cell*, std::string&&);
    std::pair<int, int> get_coord() const;
    virtual json to_json();
    virtual json get_info() const;
    virtual void Select(SceneInfo&);
    ~Entity() override = default;
};


