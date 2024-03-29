#pragma once

#include <string>
#include <source/drawable_objects/drawable_object.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Cell;
class SceneInfo;
class Player;
class PlayersEntitiesStats;

struct ClickResponse {
    bool should_remove_selection;
    bool should_reclick;
    bool should_change_selection_to_building_on_same_cell;
};

class Entity : public DrawableObject {
protected:
    Cell* cell_;
    virtual void DrawImage(Screen &screen, const GameOptions &game_options, const Vector2D &pos) const;
public:
    static const std::string kEmptyEntityName;
    const std::string image_name_;
    void Draw(Screen&, const GameOptions&) override;
    virtual ClickResponse HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) const = 0;
    Entity(Cell*, std::string);
    [[nodiscard]] std::pair<int, int> get_coord() const;
    virtual json to_json();
    [[nodiscard]] virtual json get_info() const;
    virtual void Select(const SceneInfo&) const;
    [[nodiscard]] Color get_color() const;
    virtual void NextTurn(SceneInfo& scene) = 0;
    Player& get_player();
    [[nodiscard]] size_t get_player_index() const;
    [[nodiscard]] inline const Cell* get_cell() const {
        return cell_;
    }
    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_my_turn() const;
    [[nodiscard]] const Player& get_player() const;
    [[nodiscard]] virtual bool is_passable(size_t asking_player_index) const = 0;
    ~Entity() override = default;
    [[nodiscard]] bool is_my_player(size_t another_player_index) const;
    [[nodiscard]] virtual bool is_hittable(size_t asking_player_index) const;
    [[nodiscard]] const PlayersEntitiesStats& get_player_stats() const;

};
