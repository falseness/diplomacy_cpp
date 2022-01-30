//#include <source/drawable_objects_groups/game_scene/game_scene.h>
#include <source/drawable_objects/interface_elements/triangle.h>

#pragma once

class NextTurnButton : public Triangle {
public:
    //void HandleClick(SceneInfo&, const Vector2D&, const GameOptions&);
    void Draw(Screen &, const GameOptions &) override;
};