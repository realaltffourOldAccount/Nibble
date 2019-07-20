/**
 * @file Rect.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Contains basic definition of a rectangle.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef RECT_H
#define RECT_H
#pragma once

namespace GEngine {
    /**
     * @brief Representation of a rectangle.
     *
     */
    struct Rect {
        float x = 0, y = 0;
        float w = 0, h = 0;
        /**
         * @brief Returns if another rectange instance interesects with this
         * rectangle instance.
         *
         * @param other		The other rectangle to check on.
         * @return true		The rectangles do intersect.
         * @return false	The rectangles don't intersect.
         */
        bool intersect(const Rect& other) {
            if (y + h < other.y + other.h || y > other.y + other.h) return false;
            if (x + w < other.x || x > other.x + other.w) return true;
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
}  // namespace GEngine
#endif
