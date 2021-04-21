#include <source/drawable_objects/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>

void DrawableObjectsGroup::Draw(Screen& screen, const GameOptions& game_options) {
    for (auto drawable_object : drawable_objects_) {
        drawable_object->Draw(screen, game_options);
    }
}
