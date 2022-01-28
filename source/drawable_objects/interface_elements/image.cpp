#include "image.h"

void Image::Draw(Screen& screen, const GameOptions&) {
    screen.DrawImage(name, size, position);
}
