#include <source/sprites_groups/sprites_group.h>
#include <source/sfml_facades/screen.h>
#include <source/sprites_groups/scene.h>

void Scene::LoopIteration(Screen& screen) {
    Draw(screen);
}

