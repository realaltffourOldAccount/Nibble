/**
 * @file ApplicationEvent.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definitions for application events.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef APP_EVENT_H
#define APP_EVENT_H

#include "Event.h"
#include "common.h"

namespace GEngine {

/**
 * @brief Represents a window resize event.
 *
 */
class WindowResizeEvent : public Event {
   public:
	/**
	 * @brief Construct a new Window Resize Event object
	 *
	 * @param width	The width of the window.
	 * @param height	The height of the window.
	 */
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	/**
	 * @brief Get the Width object.
	 *
	 * @return unsigned int
	 */
	inline unsigned int GetWidth() const { return m_Width; }
	/**
	 * @brief Get the Height object.
	 *
	 * @return unsigned int
	 */
	inline unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
   private:
	unsigned int m_Width, m_Height;
};

/**
 * @brief Represents a close event.
 *
 */
class WindowCloseEvent : public Event {
   public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}  // namespace GEngine

#endif