#ifndef POINT_H
#define POINT_H

struct Point {
    float x;
    float y;

    Point() {}
    Point(int _x, int _y) {x = _x; y = _y;}
};

#endif //POINT_H