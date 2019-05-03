#ifndef RECT_H
#define RECT_H

#include "chsr_api.h"

struct Rect {
    int x, y;
    int width, height;

    bool intersect(Rect other) {
        if (y + height < other.y + other.height || y > other.y + other.height)
            return false;
        if (x + width < other.x || x > other.x + other.width) return false;
        return true;
    }

    Rect() {}
    Rect(int _x, int _y, int _w, int _h) {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
    }
};

#endif
