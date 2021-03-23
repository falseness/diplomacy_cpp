#include <source/sprites/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites_groups/sprites_group.h>
#include <vector>

void SpritesGroup::Draw(Screen& screen, const GameOptions& game_options) {
    for (auto sprite : sprites_) {
        sprite->Draw(screen, game_options);
    }
}
/*
SpritesGroup::~SpritesGroup() {
    for (size_t i = 0; i < sprites_.size(); ++i) {
        delete sprites_[i];
    }
}*/
