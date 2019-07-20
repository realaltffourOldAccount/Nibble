/**
 * @file TouchEvents.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definitions for touch events.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef TOUCH_EVENTS_H
#define TOUCH_EVENTS_H

#include "Event.h"
#include "common.h"

namespace GEngine {
    /**
     * @brief Represents a touch event.
     *
     */
    class TouchEvent : public Event {
        public:
            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchEvent";
                return ss.str();
            }

            /**
             * @brief Get the touch location.
             *
             * @return double
             */
            double GetX(void) const { return _x; }
            /**
             * @brief Get the touch location.
             *
             * @return double
             */
            double GetY(void) const { return _y; }

            EVENT_CLASS_TYPE(Touch)
                EVENT_CLASS_CATEGORY(EventCategoryTouch | EventCategoryInput)
        protected:
                /**
                 * @brief Construct a new Touch Event object.
                 *
                 * @param x The location of the touch.
                 * @param y The location of the touch.
                 */
                TouchEvent(double x, double y) {
                    _x = x;
                    _y = y;
                }
                double _x;
                double _y;
    };

    /**
     * @brief Represents a touch hover event.
     *
     */
    class TouchHoverEvent : public TouchEvent {
        public:
            /**
             * @brief Construct a new Touch Hover Event object.
             *
             * @param x The location of the touch.
             * @param y	The location of the touch.
             */
            TouchHoverEvent(double x, double y) : TouchEvent(x, y) {}

            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchHover: " << _x << ", " << _y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(TouchHover)
    };

    /**
     * @brief Represents a touch began event.
     *
     */
    class TouchBeganEvent : public TouchEvent {
        public:
            /**
             * @brief Construct a new Touch Began Event object.
             *
             * @param x	The location of the touch.
             * @param y	The location of the touch.
             */
            TouchBeganEvent(double x, double y) : TouchEvent(x, y) {}

            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchBegan: " << _x << ", " << _y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(TouchBegan)
    };

    /**
     * @brief Represents a touch moved event.
     *
     */
    class TouchMovedEvent : public TouchEvent {
        public:
            /**
             * @brief Construct a new Touch Moved Event object.
             *
             * @param x	The location of the touch.
             * @param y	The location of the touch.
             */
            TouchMovedEvent(double x, double y) : TouchEvent(x, y) {}

            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchMoved: " << _x << ", " << _y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(TouchMoved)
    };

    /**
     * @brief Represents a touch cancelled event.
     *
     */
    class TouchCancelledEvent : public TouchEvent {
        public:
            /**
             * @brief Construct a new Touch Cancelled Event object.
             *
             * @param x The location of the touch.
             * @param y	THe location of the touch.
             */
            TouchCancelledEvent(double x, double y) : TouchEvent(x, y) {}

            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchCancelled: " << _x << ", " << _y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(TouchCancelled)
    };

    /**
     * @brief Represents a touch end event.
     *
     */
    class TouchEndedEvent : public TouchEvent {
        public:
            /**
             * @brief Construct a new Touch Ended Event object.
             *
             * @param x The location of the touch.
             * @param y	The location of the touch.
             */
            TouchEndedEvent(double x, double y) : TouchEvent(x, y) {}

            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "TouchEnded: " << _x << ", " << _y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(TouchEnded)
    };

}  // namespace GEngine

#endif
