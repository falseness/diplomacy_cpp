#include "source/drawable_objects_groups/game_scene/game_scene.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/utility/color.h"


GameScene::GameScene(Screen& screen, const GameOptions& game_options) : info_(screen), next_turn_button_(screen) {

    drawable_objects_.push_back(&info_.grid);
    drawable_objects_.push_back(&info_.cells_text);
    drawable_objects_.push_back(&info_.range_unit_attack_border);
    drawable_objects_.push_back(&info_.selection_border);
    drawable_objects_.push_back(&next_turn_button_);
    drawable_objects_.push_back(&info_.sudden_death_info);
    drawable_objects_.push_back(&info_.entity_interface);
    drawable_objects_.push_back(&info_.production_interface);
    drawable_objects_.push_back(&info_.town_production_interface);

    clickable_objects_.push_back(&info_.grid);
    clickable_objects_.push_back(&next_turn_button_);
    clickable_objects_.push_back(&info_.entity_interface);
    clickable_objects_.push_back(&info_.production_interface);
    clickable_objects_.push_back(&info_.town_production_interface);
}

void GameScene::HandleClick(const Vector2D& click_pos, const GameOptions& game_options) {
    info_.grid.StartUndoSequence();
    for (auto it = clickable_objects_.rbegin(); it != clickable_objects_.rend(); ++it) {
        if ((*it)->HandleClick(info_, click_pos, game_options))
            break;
    }
}

void GameScene::HandleKeyBackspacePress() {
    info_.grid.HandleKeyPress(info_);
}

void GameScene::HandleKeyEnterPress() {
    next_turn_button_.NextTurn(info_);
}

void GameScene::HandleArrowKeyPress(ArrowsKeyPressInfo arrows_info, Screen& screen, const GameOptions& game_options) {
    static const float kCameraSpeed = 0.09 * GameOptions::kMaxFPS;
    static const float kMaximumMargin = 800.0f;
    auto offset = screen.get_draw_offset();
    offset += {-static_cast<float>(arrows_info.hotizontal_sum) * kCameraSpeed,
               -static_cast<float>(arrows_info.vertical_sum) * kCameraSpeed};

    Vector2D right_bottom_corner = info_.grid.get_right_bottom_corner(game_options);
    offset.x = std::max(offset.x, -kMaximumMargin - right_bottom_corner.x + static_cast<float>(screen.get_width()));
    offset.y = std::max(offset.y, -kMaximumMargin - right_bottom_corner.y + static_cast<float>(screen.get_height()));

    Vector2D left_top_corner(-game_options.hexagon_options.radius, -game_options.hexagon_options.radius);
    offset.x = std::min(offset.x, kMaximumMargin - left_top_corner.x);
    offset.y = std::min(offset.y, kMaximumMargin - left_top_corner.y);
    screen.set_draw_offset(offset);
}

SceneInfo::SceneInfo(Screen& screen) :
        players({Color(80, 80, 80), Color(255, 0, 0), Color(0, 255, 0)}, 1), grid(players), cells_text(grid),
        selection_border(grid, Color::kWhite),
        range_unit_attack_border(grid, Color(255, 255, 255), Color(0, 0, 255)),
        entity_interface(screen), production_interface(screen),
        town_production_interface(screen),
        sudden_death_info({screen.get_width() - screen.get_height() * 0.1f, screen.get_height() * 0.04f},
                          static_cast<size_t>(screen.get_height() * 0.06), Color::kWhite, 10) {}

void SceneInfo::ClearInterfaces() {
    selection_border.Clear();
    range_unit_attack_border.Clear();
    entity_interface.set_visible(false);
    town_production_interface.set_visible(false);
    production_interface.set_visible(false);
}
