#include <source/sfml_facades/screen.h>
#include <source/drawable_objects_groups/scene.h>

void Scene::LoopIteration(Screen& screen, const GameOptions& game_options) {
    Draw(screen, game_options);
}
