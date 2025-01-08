#pragma once

#include "source/utility/color.h"
#include "source/utility/rectangle.h"


struct ColoredRectangle : public Rectangle {
    Color border_color = Color(0, 0, 0);
    // width 0 means no border
    float border_width = 5;
    Color background_color = Color(255, 0, 0);
};
