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
    scene.grid.StartUndoSequence();
    scene.players.NextTurn(scene);
    scene.grid.RemoveSelection();
    // it is important that stack clears after players.NextTurn call
    scene.grid.ClearUndoStack();
    scene.ClearInterfaces();

    background_color = scene.players[scene.players.get_whoose_turn()].get_color();
}

bool NextTurnButton::HandleClick(SceneInfo& scene, const Vector2D& pos, const GameOptions &) {
    if (is_inside(pos)) {
        NextTurn(scene);
        return true;
    }
    return false;
}
