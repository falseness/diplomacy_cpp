#include <source/drawable_objects/drawable_object.h>
#include <string>

#pragma once

struct Text : public DrawableObject {
    Vector2D position{100, 100};
    std::string text = "error";
    size_t size = 24;
    Color color = Color(255, 255, 255);
    [[nodiscard]] float get_height(const Screen&) const;
    [[nodiscard]] float get_width(const Screen&) const;
    void set_center(Vector2D pos, const Screen&);
    void Draw(Screen&, const GameOptions&) override;
};

class RightAlignedText : public Text {
    void Draw(Screen&, const GameOptions&) override;
};
