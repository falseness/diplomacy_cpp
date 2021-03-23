#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites_groups/sprites_group.h>
#include <vector>

void SpritesGroup::Draw(Screen& screen) {
    for (auto sprite : sprites_) {
        sprite->Draw(screen);
    }
}
