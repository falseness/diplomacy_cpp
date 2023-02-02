#include "player0.h"

#include "source/drawable_objects_groups/game_scene/game_scene.h"


void Player0::NextTurn(SceneInfo &scene) {
    Player::NextTurn(scene);

    int turns_after_sudden_death = -scene.sudden_death_info.get_turns_left();
    if (turns_after_sudden_death < 0) {
        return;
    }


}
