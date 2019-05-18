#ifndef TOUCH_EVENTS_H
#define TOUCH_EVENTS_H

#include "Event.h"
#include "common.h"

namespace GEngine {
class TouchEvent : public Event {
  public:
    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchEvent";
        return ss.str();
    }

    double GetX(void) const { return _x; }
    double GetY(void) const { return _y; }

    EVENT_CLASS_TYPE(Touch)
    EVENT_CLASS_CATEGORY(EventCategoryTouch | EventCategoryInput)
  protected:
    TouchEvent(double x, double y) {
        _x = x;
        _y = y;
    }
    double _x;
    double _y;
};

class TouchHoverEvent : public TouchEvent {
  public:
    TouchHoverEvent(double x, double y) : TouchEvent(x, y) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchHover: " << _x << ", " << _y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(TouchHover)
};

class TouchBeganEvent : public TouchEvent {
  public:
    TouchBeganEvent(double x, double y) : TouchEvent(x, y) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchBegan: " << _x << ", " << _y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(TouchBegan)
};

class TouchMovedEvent : public TouchEvent {
  public:
    TouchMovedEvent(double x, double y) : TouchEvent(x, y) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchMoved: " << _x << ", " << _y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(TouchMoved)
};

class TouchCancelledEvent : public TouchEvent {
  public:
    TouchCancelledEvent(double x, double y) : TouchEvent(x, y) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchCancelled: " << _x << ", " << _y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(TouchCancelled)
};

class TouchEndedEvent : public TouchEvent {
  public:
    TouchEndedEvent(double x, double y) : TouchEvent(x, y) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "TouchEnded: " << _x << ", " << _y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(TouchEnded)
};

} // namespace GEngine

#endif