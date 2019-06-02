/**
 * @file WindowBase.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains the bases of a cross-platform window.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

#include <engine/Timer.h>

namespace GEngine {
namespace Window {

/**
 * @brief The desired update rate per second.
 *
 */
const static int desiredTickRate = 128;
/**
 * @brief The max skip frames allowed.
 *
 */
const int maxSkipFrames = 10;

/**
 * @brief The Window State representation.
 *
 */
struct WindowState {
	int _win_width, _win_height;
	int _mouse_pos_x, _mouse_pos_y;
	bool _isMouseIn = true;

	bool _paused = false;
	bool _loading = false;
};

/**
 * @brief The bases of a cross-platform window.
 *
 */
class WindowBase {
   public:
	/**
	 * @brief The Event callback function.
	 *
	 */
	using EventCallbackFn = std::function<void(Event& e)>;

	/**
	 * @brief Set the Event Handler object.
	 *
	 * @param callback The Callback to set.
	 */
	void setEventHandler(const EventCallbackFn& callback);

	/**
	 * @brief Starts the window.
	 *
	 */
	virtual void start(void) = 0;
	/**
	 * @brief Destroys the window.
	 *
	 */
	virtual void destroy(void) = 0;

	/**
	 * @brief Get the State object.
	 *
	 * @return WindowState
	 */
	WindowState getState(void) const;
	/**
	 * @brief Get the MVP.
	 *
	 * @return MVP*
	 */
	MVP* getMVP(void) const;
	/**
	 * @brief Get the Proj object.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getProj(void) const;

	/**
	 * @brief Get the MSPF object.
	 *
	 * @return long double
	 */
	long double getMSPF(void) const;
	/**
	 * @brief Get the UT object.
	 *
	 * @return long double
	 */
	long double getUT(void) const;

	// Custom Events
   public:
	/**
	 * @brief Custom event for updating.
	 *
	 */
	virtual void tick(void) = 0;
	/**
	 * @brief Custom event for rendering.
	 *
	 */
	virtual void render(void) = 0;
	/**
	 * @brief Custom event for initializing.
	 *
	 */
	virtual void init(void) = 0;

   protected:
	WindowBase(void);
	~WindowBase(void);

	WindowState _state;
	MVP* _mvp = nullptr;
	glm::mat4 _projection = glm::mat4(1.0f);

	EventCallbackFn EventCallback;

	Timer* timer = nullptr;
	long double mspf = 0.0;
	long double ut = 0.0;

   public:
	/**
	 * @brief Window Class initialization function.
	 *
	 * @param w		The width of the function.
	 * @param h		The height of the function.
	 * @param str	The title of the function.
	 */
	virtual void __init(int w, int h, std::string str) = 0;
	/**
	 * @brief Window Class Loop function.
	 *
	 */
	virtual void __loop(void) = 0;
	/**
	 * @brief Window Class one iteration function.
	 *
	 */
	virtual void __iter(void);
	/**
	 * @brief Window Class Underhood tick function.
	 *
	 */
	virtual void __underhood_tick(void);
	/**
	 * @brief Updates the MVP function.
	 *
	 */
	virtual void __update_mvp(void);
};
}  // namespace Window
}  // namespace GEngine
#endif