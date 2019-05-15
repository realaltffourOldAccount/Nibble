#include "Window.h"

GEngine::Window::Window(bool auto_size, int width, int height,
                        std::string title) {
#ifndef __EMSCRIPTEN__
    if (auto_size) {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        this->__init(mode->width, mode->height, title);
    } else
#endif
        this->__init(width, height, title);
}

GEngine::Window::~Window(void) { this->destroy(); }

void GEngine::Window::setEventHandler(const EventCallbackFn& callback) {
    EventCallback = callback;
}

GEngine::WindowState GEngine::Window::getState(void) const {
    return this->_state;
}
GEngine::MVP* GEngine::Window::getMVP(void) const { return this->_mvp; }
glm::mat4 GEngine::Window::getProj(void) const { return this->_projection; }

static GEngine::Window* window_ptr = nullptr;
static void __em_loop(void) { window_ptr->__iter(); }
void GEngine::Window::start(void) {
#ifndef __EMSCRIPTEN__
    this->__loop();
#else
    Log::info("Started Game Loop.");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    window_ptr = this;
    emscripten_set_main_loop(__em_loop, 60, 1);
#endif
}

void GEngine::Window::destroy(void) { glfwDestroyWindow(this->_window); }

void GEngine::Window::__init(int w, int h, std::string str) { // Create window
    this->_window = glfwCreateWindow(w, h, str.c_str(), NULL, NULL);
    if (this->_window == NULL) {
        THROW_ERROR("Failed Window Creation.");
        return;
    } else
        Log::info("Window Created.");
    // Create Context
    glfwMakeContextCurrent(this->_window);
    initGLAD();
    // Set event listeners
    glfwSetWindowUserPointer(this->_window, this);

    glfwSetFramebufferSizeCallback(this->_window, resize_callback);
    glfwSetKeyCallback(this->_window, key_callback);
    glfwSetCursorPosCallback(this->_window, cursor_pos_callback);
    glfwSetCursorEnterCallback(this->_window, cursor_enter_callback);
    glfwSetMouseButtonCallback(this->_window, mouse_button_callback);
    // Cap fps
    glfwSwapInterval(0);

    // Set up state
    glfwGetFramebufferSize(this->_window, &(this->_state._win_width),
                           &(this->_state._win_height));

    // Set up mvp
    this->_mvp = new GEngine::MVP();
    this->__update_mvp();
}
void GEngine::Window::__loop(void) {
    Log::info("Started Game Loop.");
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    while (!glfwWindowShouldClose(this->_window)) {
        this->__iter();
    }
}
void GEngine::Window::__iter(void) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    this->render();
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
    this->tick();
}
void GEngine::Window::__underhood_tick(void) {}

void GEngine::Window::__update_mvp(void) {
    this->_projection =
        glm::ortho(0, this->_state._win_width, 0, this->_state._win_height);
    this->_mvp->updateProj(this->_projection);
}

void GEngine::Window::OnResize(int width, int height) {
    this->_state._win_width = width;
    this->_state._win_height = height;
    this->__update_mvp();

    GEngine::WindowResizeEvent event(width, height);
    this->EventCallback(event);
}
void GEngine::Window::OnMousePos(double xpos, double ypos) {
    this->_state._mouse_pos_x = xpos;
    this->_state._mouse_pos_y = ypos;

    GEngine::MouseMovedEvent event(xpos, ypos);
    this->EventCallback(event);
}
void GEngine::Window::OnCursorEntered(void) {
    this->_state._isMouseIn = true;

    GEngine::MouseEnteredEvent event;
    this->EventCallback(event);
}
void GEngine::Window::OnCursorExit(void) {
    this->_state._isMouseIn = false;

    GEngine::MouseExitedEvent event;
    this->EventCallback(event);
}

void GEngine::Window::OnKey(int key, int scancode, int action, int mods) {
    switch (action) {
    case GLFW_PRESS: {
        GEngine::KeyPressedEvent event(key, 0);
        this->EventCallback(event);
        break;
    }
    case GLFW_RELEASE: {
        GEngine::KeyReleasedEvent event(key);
        this->EventCallback(event);
        break;
    }
    case GLFW_REPEAT: {
        GEngine::KeyPressedEvent event(key, 1);
        this->EventCallback(event);
    }
    }
}
void GEngine::Window::OnMouseButton(int button, int action, int mods) {
    switch (action) {
    case GLFW_PRESS: {
        GEngine::MouseButtonPressedEvent event(button);
        this->EventCallback(event);
        break;
    }
    case GLFW_RELEASE: {
        GEngine::MouseButtonReleasedEvent event(button);
        this->EventCallback(event);
        break;
    }
    }
}