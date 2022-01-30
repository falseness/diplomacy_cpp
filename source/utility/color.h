#pragma once

#include <cstdint>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    Color(uint8_t, uint8_t, uint8_t);
    static const Color kWhite;
    //Color(const Color&);
};
