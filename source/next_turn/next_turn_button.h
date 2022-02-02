#include <source/drawable_objects/interface_elements/triangle.h>
#include <source/drawable_objects/clickable_object.h>

#pragma once

class SceneInfo;

class NextTurnButton : public Triangle, public ClickableObject {
    void NextTurn(SceneInfo&);
public:
    explicit NextTurnButton(Screen&);
    bool HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) override;
    void Draw(Screen &, const GameOptions &) override;
};