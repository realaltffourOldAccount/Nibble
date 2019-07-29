/**
 * @file Event.h
 * @author Ayham Mamoun (ayhamaboualfadl@gail.com)
 * @brief Contains the definition of an Event.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef EVENT_H
#define EVENT_H

#include "Log.h"
#include "common.h"
#include "config.h"

namespace GEngine {
    /**
     * @brief The list of event types.
     *
     */
    enum class EventType {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,
        MouseEntered,
        MouseExited,
        MouseState,
        Touch,
        TouchHover,
        TouchBegan,
        TouchMoved,
        TouchCancelled,
        TouchEnded
    };

    /**
     * @brief The list of event categories.
     *
     */
    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseState = BIT(4),
        EventCategoryMouseButton = BIT(5),
        EventCategoryTouch = BIT(6),
    };

#define EVENT_CLASS_TYPE(type)                                   \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override {            \
        return GetStaticType();                                  \
    }                                                            \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    /**
     * @brief Basic Event representation.
     *
     */
    class Event {
        public:
            /**
             * @brief True if the event is handled and shouldn't be propagated further.
             *
             */
            bool Handled = false;
            /**
             * @brief Get the Event Type object.
             *
             * @return EventType
             */
            virtual EventType GetEventType() const = 0;
            /**
             * @brief Get the Name object.
             *
             * @return const char*
             */
            virtual const char* GetName() const = 0;
            /**
             * @brief Get the Category Flags object.
             *
             * @return int
             */
            virtual int GetCategoryFlags() const = 0;
            /**
             * @brief Converts the event to a basic string representation.
             *
             * @return std::string
             */
            virtual std::string ToString() const { return GetName(); }

            /**
             * @brief Checks if the event is in a specific category.
             *
             * @param category	The cotegory to be checked against.
             * @return true		The event have this category.
             * @return false	The event doesn't have this category.
             */
            inline bool IsInCategory(EventCategory category) {
                return GetCategoryFlags() & category;
            }
    };

    /**
     * @brief Definition of an Event Queue.
     *
     */
    class EventQueue {
        public:
            /**
             * @brief Construct a new Event Queue object
             *
             */
            EventQueue(void) {}
            /**
             * @brief Destroy the Event Queue object
             *
             */
            ~EventQueue(void) {}

            /**
             * @brief Queue Event.
             *
             * @param evt The event to queue.
             */
            void QueueEvent(Event* evt) { this->mQueue.push_back(evt); }
            /**
             * @brief Removes the first event from the queue.
             *
             */
            void UnQueueEvent() { this->mQueue.pop_front(); }

            /**
             * @brief Get the first Event object.
             *
             * @return Event* The last
             */
            Event* GetEvent() { return this->mQueue.front(); }

            /**
             * @brief Returns the size of the queue.
             *
             * @return int The size.
             */
            int size() { return mQueue.size(); }

            std::deque<Event*> mQueue;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }

}  // namespace GEngine

#endif
