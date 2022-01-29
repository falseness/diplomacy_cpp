#include <source/drawable_objects/drawable_object.h>
#include <source/sfml_facades/screen.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>

void DrawableObjectsGroup::Draw(Screen& screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    for (auto drawable_object : drawable_objects_) {
        drawable_object->Draw(screen, game_options);
    }
}

void DrawableObjectsGroup::set_visible(bool visible) {
    visible_ = visible;
}
