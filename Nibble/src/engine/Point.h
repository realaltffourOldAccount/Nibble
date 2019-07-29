/**
 * @file Point.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains basic definition of a point.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef POINT_H
#define POINT_H
#pragma once
#include <math.h>

namespace GEngine {
    /**
     * @brief Representation of a point.
     *
     */
    struct Point {
        float x, y;

        Point() {}
        Point(float _x, float _y) {
            x = _x;
            y = _y;
        }
        /**
         * @brief Returns the distances between two points.
         *
         * @param pnt		The other point.
         * @return float	The distance between the two points.
         */
        float dist(const Point& pnt) const {
            return sqrt(pow(pnt.x - this->x, 2) + pow((pnt.y - this->y), 2));
        }
    };
}  // namespace GEngine
#endif
