#pragma once

#include "source/utility/colored_rectangle.h"
#include "source/sfml_facades/screen.h"
#include "source/options/game.h"


void DrawEntityBar(const unsigned int current_value, const unsigned int maximum_value,
                   const Vector2D& position, const Vector2D& size_ratio,
                   const Color& presence_color, const Color& absence_color,
                   const RectangleBuffer buffer_type, Screen& screen, const GameOptions& game_options);