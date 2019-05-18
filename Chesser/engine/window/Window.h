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
// This window Class is used for desktop/Browser
#if (!defined(__ANDROID__))
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
#endif

#ifdef __ANDROID__
// This window Class is used for android
class Window {
  public:
    using EventCallbackFn = std::function<void(GEngine::Event& e)>;

    Window(GLFMDisplay* display);
    ~Window(void);

    void setEventHandler(const EventCallbackFn& callback);

    void start(void);
    void destroy(void);

    WindowState getState(void) const;
    GEngine::MVP* getMVP(void) const;
    glm::mat4 getProj(void) const;

    EventCallbackFn EventCallback;
    WindowState _state;

  protected: // Custom Events
    virtual void tick(void) = 0;
    virtual void render(void) = 0;
    virtual void init(void) = 0;

  private: // Vars
    GLFMDisplay* _window;
    GEngine::MVP* _mvp = nullptr;
    glm::mat4 _projection = glm::mat4(1.0f);

  public: // Funcs
    void __init(GLFMDisplay* display);
    void __surfaceCreated(void);
    void __surfaceDestroyed(void);
    void __iter(void);
    void __underhood_tick(void);
    void __update_mvp(void);
};

static void onSurfaceCreated(GLFMDisplay* display, const int width,
                             const int height) {
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    win->__surfaceCreated();
}

static void onSurfaceResized(GLFMDisplay* display, const int width,
                             const int height) {
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    win->_state._win_width = width;
    win->_state._win_height = height;
    win->__update_mvp();

    GEngine::WindowResizeEvent event(width, height);
    win->EventCallback(event);
}

static void onSurfaceDestroyed(GLFMDisplay* display) {
    // When the surface is destroyed, all existing GL resources are no longer
    // valid.
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    win->__surfaceDestroyed();
}

static void onFrame(GLFMDisplay* display, const double frameTime) {
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    win->__iter();
}

static bool onTouch(GLFMDisplay* display, int touch, GLFMTouchPhase phase,
                    double x, double y) {
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    switch (phase) {
    case GLFMTouchPhaseBegan: {
        GEngine::TouchBeganEvent event(x, y);
        win->EventCallback(event);
        break;
    }
    case GLFMTouchPhaseMoved: {
        GEngine::TouchMovedEvent event(x, y);
        win->EventCallback(event);
        break;
    }
    case GLFMTouchPhaseEnded: {
        GEngine::TouchEndedEvent event(x, y);
        win->EventCallback(event);
        break;
    }
    case GLFMTouchPhaseCancelled: {
        GEngine::TouchCancelledEvent event(x, y);
        win->EventCallback(event);
        break;
    }
    case GLFMTouchPhaseHover: {
        GEngine::TouchHoverEvent event(x, y);
        win->EventCallback(event);
        break;
    }
    default:
        return false;
        break;
    }
    return true;
}

static bool onKey(GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action,
                  int modifiers) {
    Window* win = static_cast<Window*>(glfmGetUserData(display));
    switch (action) {
    case GLFMKeyActionPressed: {
        GEngine::KeyPressedEvent event(keyCode, 0);
        win->EventCallback(event);
        break;
    }
    case GLFMKeyActionReleased: {
        GEngine::KeyReleasedEvent event(keyCode);
        win->EventCallback(event);
        break;
    }
    case GLFMKeyActionRepeated: {
        GEngine::KeyPressedEvent event(keyCode, 1);
        win->EventCallback(event);
        break;
    }
    default:
        return false;
        break;
    }
    return true;
}

#endif

} // namespace GEngine

#endif