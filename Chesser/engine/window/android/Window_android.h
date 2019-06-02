/**
 * @file Window_android.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains window definition to be run on android.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef WINDOW_ANDROID_H
#define WINDOW_ANDROID_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

#include <engine/Timer.h>
#include <engine/window/WindowBase.h>

namespace GEngine {
namespace Window {
/**
 * @brief This window Class is used for android
 *
 */
#if defined(__ANDROID__)
class Window : public WindowBase {
   public:
	Window(GLFMDisplay* display);
	~Window(void);

	void start(void) override;
	void destroy(void) override;

   private:  // Vars
	GLFMDisplay* _window;

	double deltaUpdateInterval = 0.0;
	long double accumulatedTime = 0.0;
	int nLoops = 0;

	const int desiredFPS = 30;
	double deltaFrameInterval = 0.0;

	std::chrono::high_resolution_clock::time_point lastTime;
	int nbFrames = 0;

	std::chrono::high_resolution_clock::time_point lastTimeTick;
	int nbTicks = 0;

   public:  // Funcs
	void __init(int w, int h, std::string str) override {}
	void __init(GLFMDisplay* display);
	void __loop(void) override {}
	void __iter(void) override;

   public:
	/**
	 * @brief Function Called when android surface is created.
	 *
	 */
	void OnSurfaceCreated(void);
	/**
	 * @brief Function Called when android surface is destroyed.
	 *
	 */
	void OnSurfaceDestroyed(void);
	/**
	 * @brief Function Called when android surface is resized.
	 *
	 * @param display	The android's display pointer.
	 * @param width		The width of the android's surface.
	 * @param hieght	The height of the android's surface.
	 */
	void OnSurfaceResized(GLFMDisplay* display, const int width,
						  const int hieght);
	/**
	 * @brief Function Called every frame of the execution.
	 *
	 * @param display		The android's display pointer.
	 * @param frameTime		The frame time in ms.
	 */
	void OnFrame(GLFMDisplay* display, const double frameTime);
	/**
	 * @brief Function Called when the android's surface is touched.
	 *
	 * @param display	The android's display pointer.
	 * @param touch		The number of the touch.
	 * @param phase		The current touch phase, ex: TouchMove, TouchBegin.
	 * @param x			The location of the touch.
	 * @param y			The location of the touch.
	 */
	void OnTouch(GLFMDisplay* display, int touch, GLFMTouchPhase phase,
				 double x, double y);
	/**
	 * @brief Function Called when a key event is created.
	 *
	 * @param display	The android's display pointer.
	 * @param keyCode	The key's code.
	 * @param action	The key action, ex: KeyReleased, KeyPressed.
	 * @param modifiers	The Key modifiers.
	 */
	void OnKey(GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action,
			   int modifiers);
};

static void onSurfaceCreated(GLFMDisplay* display, const int width,
							 const int height) {
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnSurfaceCreated();
}

static void onSurfaceResized(GLFMDisplay* display, const int width,
							 const int height) {
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnSurfaceResized(display, width, height);
}

static void onSurfaceDestroyed(GLFMDisplay* display) {
	// When the surface is destroyed, all existing GL resources are no longer
	// valid.
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnSurfaceDestroyed();
}

static void onFrame(GLFMDisplay* display, const double frameTime) {
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnFrame(display, frameTime);
}

static bool onTouch(GLFMDisplay* display, int touch, GLFMTouchPhase phase,
					double x, double y) {
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnTouch(display, touch, phase, x, y);
	return true;
}

static bool onKey(GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action,
				  int modifiers) {
	GEngine::Window::Window* win =
		static_cast<GEngine::Window::Window*>(glfmGetUserData(display));
	win->OnKey(display, keyCode, action, modifiers);
	return true;
}
#endif
}  // namespace Window
}  // namespace GEngine
#endif