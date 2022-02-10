#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>

#pragma once

struct RoundedRectangleWithText : public RoundedRectangle {
    Text text;
    void Draw(Screen&, const GameOptions&) override;
};
