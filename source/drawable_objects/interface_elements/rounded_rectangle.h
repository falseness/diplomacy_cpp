#pragma once

#include "source/drawable_objects/drawable_object.h"
#include "source/utility/vector2d.h"
#include "source/utility/color.h"
#include "source/utility/colored_rectangle.h"


struct RoundedRectangle : ColoredRectangle, DrawableObject {
    // radius 0 means no circle
    float corner_radius = 30;
    void Draw(Screen&, const GameOptions&) override;
};
