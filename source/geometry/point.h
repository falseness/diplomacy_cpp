#ifndef DIPLOMACY_POINT_H
#define DIPLOMACY_POINT_H

struct Point {
    float x;
    float y;
    Point(float init_x = 0, float init_y = 0) : x(init_x), y(init_y) {}
};

#endif //DIPLOMACY_POINT_H
