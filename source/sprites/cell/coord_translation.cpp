#include "coord_translation.h"

std::pair<int, int> bias_to_transition(int x, int y) {
    /*
        even basis
        y = y - (x - (x & 1)) / 2 (to axial)
        by = 2 * y + x
    */
    return std::make_pair(x, 2 * y + (x & 1));
}