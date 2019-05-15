#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

namespace GEngine {

struct WindowState {
    int _win_width, _win_height;
    int _mouse_pos_x, _mouse_pos_y;
    bool _isMouseIn = true;
};
// This window is used for desktop/Browser
class Window {
  public:
    using EventCallbackFn = std::function<void(GEngine::Event& e)>;

    Window(bool auto_size, int width, int height, std::string title);
    ~Window(void);

    void setEventHandler(const EventCallbackFn& callback);

    void start(void);
    void destroy(void);

    WindowState getState(void) const;
    GEngine::MVP* getMVP(void) const;
    glm::mat4 getProj(void) const;

  protected: // Custom Events
    virtual void tick(void) = 0;
    virtual void render(void) = 0;

  private: // Vars
    GLFWwindow* _window;
    WindowState _state;
    GEngine::MVP* _mvp = nullptr;
    glm::mat4 _projection = glm::mat4(1.0f);

    EventCallbackFn EventCallback;

  public: // Funcs
    void __init(int w, int h, std::string str);
    void __loop(void);
    void __iter(void);
    void __underhood_tick(void);
    void __update_mvp(void);

  public: // GLFW Events Funcs
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
    GEngine::Window* win = static_cast<GEngine::Window*>(data);

    win->OnMouseButton(button, action, mods);
}

static void cursor_enter_callback(GLFWwindow* window, int entered) {
    void* data = glfwGetWindowUserPointer(window);
    GEngine::Window* win = static_cast<GEngine::Window*>(data);

    if (entered)
        win->OnCursorEntered();
    else
        win->OnCursorExit();
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    void* data = glfwGetWindowUserPointer(window);
    GEngine::Window* win = static_cast<GEngine::Window*>(data);
    win->OnMousePos(xpos, ypos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    void* data = glfwGetWindowUserPointer(window);
    GEngine::Window* win = static_cast<GEngine::Window*>(data);
    win->OnKey(key, scancode, action, mods);
}
static void resize_callback(GLFWwindow* window, int width, int height) {
    void* data = glfwGetWindowUserPointer(window);
    GEngine::Window* win = static_cast<GEngine::Window*>(data);
    win->OnResize(width, height);
}

} // namespace GEngine

#endif