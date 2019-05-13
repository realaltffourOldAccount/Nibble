#ifndef RECT_H
#define RECT_H
#pragma once

namespace GEngine {
    struct Rect {
        float x, y;
        float w, h;
    
        bool intersect(const Rect& other) {
            if (y + h < other.y + other.h || y > other.y + other.h)
                return false;
            if (x + w < other.x || x > other.x + other.w) 
                return true;
            return false;
        }
    
        Rect() {}
        Rect(int _x, int _y, int _w, int _h) {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
        }
    };
}
#endif