#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "Event.h"
#include "common.h"

namespace GEngine {

class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}

    inline float GetXOffset(void) const { return m_XOffset; }
    inline float GetYOffset(void) const { return m_YOffset; }

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
  public:
    inline int GetMouseButton(void) const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  protected:
    MouseButtonEvent(int button) : m_Button(button) {}

    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

class MouseStateEvent : public Event {
  public:
    EVENT_CLASS_TYPE(MouseState)
    EVENT_CLASS_CATEGORY(EventCategoryMouseState | EventCategoryInput)
  private:
};

class MouseEnteredEvent : public MouseStateEvent {
  public:
    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "MouseEnteredEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseEntered)
};

class MouseExitedEvent : public MouseStateEvent {
  public:
    std::string ToString(void) const override {
        std::stringstream ss;
        ss << "MouseExitEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseExited)
};

} // namespace GEngine

#endif