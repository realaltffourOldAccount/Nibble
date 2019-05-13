#ifndef POINT_H
#define POINT_H
#pragma once
#include <math.h>

namespace GEngine {
    struct Point {
        float x, y;
        
        Point() {}
        Point(float _x, float _y) {x=_x; y=_y;}
    
        float dist(const Point& pnt) const {
            return sqrt(pow(pnt.x-this->x, 2)+pow((pnt.y-this->y), 2));
        }
    };
}
#endif