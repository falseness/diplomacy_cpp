#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites_groups/sprites_group.h>

void SpritesGroup::Draw(Screen& screen, const GameOptions& game_options) {
    for (auto sprite : sprites_) {
        sprite->Draw(screen, game_options);
    }
}
