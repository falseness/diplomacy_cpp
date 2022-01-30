#pragma once

class SceneInfo;
class Vector2D;
class GameOptions;

class ClickableObject {
public:
    virtual bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) = 0;
    virtual ~ClickableObject() = default;
};
