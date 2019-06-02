/**
 * @file KeyEvent.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Contains the definitions for key events.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "Event.h"
#include "common.h"

namespace GEngine {

/**
 * @brief Represents a basic key event.
 *
 */
class KeyEvent : public Event {
   public:
	/**
	 * @brief Get the Key Code object.
	 *
	 * @return int
	 */
	inline int GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
   protected:
	KeyEvent(int keycode) : m_KeyCode(keycode) {}

	int m_KeyCode;
};

/**
 * @brief Represents a pressed key event.
 *
 */
class KeyPressedEvent : public KeyEvent {
   public:
	/**
	 * @brief Construct a new Key Pressed Event object.
	 *
	 * @param keycode			The key code of the object.
	 * @param repeatCount	The number of repeats of the key.
	 */
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

	/**
	 * @brief Get the Repeat Count object.
	 *
	 * @return int
	 */
	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
		   << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
   private:
	int m_RepeatCount;
};

/**
 * @brief Represents a released event.
 *
 */
class KeyReleasedEvent : public KeyEvent {
   public:
	/**
	 * @brief Construct a new Key Released Event object.
	 *
	 * @param keycode	The key code of the event.
	 */
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

/**
 * @brief Represents a key typed event.
 *
 */
class KeyTypedEvent : public KeyEvent {
   public:
	/**
	 * @brief Construct a new Key Typed Event object.
	 *
	 * @param keycode	The key code of the event.
	 */
	KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace GEngine

#endif