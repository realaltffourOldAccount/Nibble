#ifndef WINDOW_DESKTOP_H
#define WINDOW_DESKTOP_H
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
// This window Class is used for Desktop
#if defined(__DESKTOP__)
class Window : public GEngine::Window::WindowBase {
   public:
	Window(bool auto_size, int width, int height, std::string title);
	~Window(void);

	void start(void) override;
	void destroy(void) override;

   private:  // Vars
	GLFWwindow* _window;

   public:
	void __init(int w, int h, std::string str) override;
	void __loop(void) override;

   public:  // GLFW Events Funcs
	void OnKey(int key, int scancode, int action, int mods);
	void OnMouseButton(int button, int action, int mods);
	void OnResize(int width, int height);
	void OnMousePos(double xpos, double ypos);
	void OnCursorEntered(void);
	void OnCursorExit(void);
};

static void mouse_button_callback(GLFWwindow* window, int button, int action,
								  int mods) {
	void* data = glfwGetWindowUserPointer(window);
	GEngine::Window::Window* win = static_cast<GEngine::Window::Window*>(data);

	win->OnMouseButton(button, action, mods);
}

static void cursor_enter_callback(GLFWwindow* window, int entered) {
	void* data = glfwGetWindowUserPointer(window);
	GEngine::Window::Window* win = static_cast<GEngine::Window::Window*>(data);

	if (entered)
		win->OnCursorEntered();
	else
		win->OnCursorExit();
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	void* data = glfwGetWindowUserPointer(window);
	Window* win = static_cast<Window*>(data);
	win->OnMousePos(xpos, ypos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
						 int mods) {
	void* data = glfwGetWindowUserPointer(window);
	Window* win = static_cast<Window*>(data);
	win->OnKey(key, scancode, action, mods);
}
static void resize_callback(GLFWwindow* window, int width, int height) {
	void* data = glfwGetWindowUserPointer(window);
	Window* win = static_cast<Window*>(data);
	win->OnResize(width, height);
}
#endif
}  // namespace Window
}  // namespace GEngine
#endif