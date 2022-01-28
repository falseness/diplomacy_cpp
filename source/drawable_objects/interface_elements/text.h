#include <source/drawable_objects/drawable_object.h>
#include <string>

#pragma once

struct Text : public DrawableObject {
    Vector2D position{100, 100};
    std::string text = "error";
    size_t size = 24;
    Color color = Color(255, 255, 255);
    void Draw(Screen&, const GameOptions&) override;
};