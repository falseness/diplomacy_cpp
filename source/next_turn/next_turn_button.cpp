#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include "next_turn_button.h"

void NextTurnButton::Draw(Screen& screen, const GameOptions &) {
    screen.DrawTriangle(*this);
}

NextTurnButton::NextTurnButton(Screen& screen) {
    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    side = w * 0.1f;
    position.x = w - side * 1.05f;
    position.y = h - side * 1.05f;
}

void NextTurnButton::NextTurn(SceneInfo& scene) {
    scene.players.NextTurn();
    scene.grid.RemoveSelection();
    scene.entity_interface.set_visible(false);
    scene.production_interface.set_visible(false);

    background_color = scene.players[scene.players.get_whoose_turn()].get_color();
}

bool NextTurnButton::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions &) {
    if (is_inside(pos)) {
        NextTurn(scene);
        return true;
    }
    return false;
}
