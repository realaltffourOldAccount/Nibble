/**
 * @file MouseEvents.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Contains the definitions for mouse events.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "Event.h"
#include "common.h"

namespace GEngine {

    /**
     * @brief Represents a basic mouse event.
     *
     */
    class MouseMovedEvent : public Event {
        public:
            /**
             * @brief Construct a new Mouse Moved Event object.
             *
             * @param x	The location of the mouse.
             * @param y	The location of the mouse.
             */
            MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

            /**
             * @brief Gets the location of the mouse.
             *
             * @return float
             */
            inline float GetX() const { return m_MouseX; }
            /**
             * @brief Gets the location of the mouse.
             *
             * @return float
             */
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

    /**
     * @brief Represents a scroll mouse event.
     *
     */
    class MouseScrolledEvent : public Event {
        public:
            /**
             * @brief Construct a new Mouse Scrolled Event object.
             *
             * @param xOffset The Offset scrolled.
             * @param yOffset The Offset scrolled.
             */
            MouseScrolledEvent(float xOffset, float yOffset)
                : m_XOffset(xOffset), m_YOffset(yOffset) {}

            /**
             * @brief Gets the offset scrolled.
             *
             * @return float
             */
            inline float GetXOffset(void) const { return m_XOffset; }
            /**
             * @brief Gets the offset scrolled.
             *
             * @return float
             */
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

    /**
     * @brief Represents a button action event.
     *
     */
    class MouseButtonEvent : public Event {
        public:
            /**
             * @brief Get the Mouse Button object
             *
             * @return int
             */
            inline int GetMouseButton(void) const { return m_Button; }

            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        protected:
                MouseButtonEvent(int button) : m_Button(button) {}

                int m_Button;
    };

    /**
     * @brief Represents a mouse button pressed event.
     *
     */
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

    /**
     * @brief Represents a mouse buttono released event.
     *
     */
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

    /**
     * @brief Represents a mouse state change event.
     *
     */
    class MouseStateEvent : public Event {
        public:
            EVENT_CLASS_TYPE(MouseState)
                EVENT_CLASS_CATEGORY(EventCategoryMouseState | EventCategoryInput)
        private:
    };

    /**
     * @brief Represents a mouse enter window state change event.
     *
     */
    class MouseEnteredEvent : public MouseStateEvent {
        public:
            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "MouseEnteredEvent";
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseEntered)
    };

    /**
     * @brief Represents a mouse exit window state change event.
     *
     */
    class MouseExitedEvent : public MouseStateEvent {
        public:
            std::string ToString(void) const override {
                std::stringstream ss;
                ss << "MouseExitEvent";
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseExited)
    };

}  // namespace GEngine

#endif
