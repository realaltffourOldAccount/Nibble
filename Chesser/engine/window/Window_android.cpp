#include "Window.h"

#ifdef __ANDROID__

GEngine::Window::Window(GLFMDisplay* display) { this->__init(display); }
GEngine::Window::~Window(void) { this->destroy(); }

void GEngine::Window::setEventHandler(const EventCallbackFn& callback) {
    EventCallback = callback;
}

void GEngine::Window::start(void) {
    // Does nothing,
    // In android there can't be endless loops.
}
void GEngine::Window::destroy(void) {}

GEngine::WindowState GEngine::Window::getState(void) const {
    return this->_state;
}
GEngine::MVP* GEngine::Window::getMVP(void) const { return this->_mvp; }
glm::mat4 GEngine::Window::getProj(void) const { return this->_projection; }

void GEngine::Window::__init(GLFMDisplay* display) {
    this->_window = display;
    glfmSetDisplayConfig(display, GLFMRenderingAPIOpenGLES3,
                         GLFMColorFormatRGBA8888, GLFMDepthFormatNone,
                         GLFMStencilFormatNone, GLFMMultisampleNone);
    glfmSetUserData(display, this);
    glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);
    glfmSetSurfaceResizedFunc(display, onSurfaceResized);
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
    glfmSetMainLoopFunc(display, onFrame);
    glfmSetTouchFunc(display, onTouch);
    glfmSetKeyFunc(display, onKey);
    g_engine_init = true;
}
void GEngine::Window::__iter(void) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    if (g_opengl_init) {
        this->render();
        this->tick();
    }
}
void GEngine::Window::__underhood_tick(void) {}
void GEngine::Window::__update_mvp(void) {
    this->_projection =
        glm::ortho(0, this->_state._win_width, 0, this->_state._win_height);
    this->_mvp->updateProj(this->_projection);
}

void GEngine::Window::__surfaceCreated(void) {
    Log::info("Surface Created");
    glfmGetDisplaySize(this->_window, &this->_state._win_width,
                       &this->_state._win_height);
    g_opengl_init = true;
    init();
}
void GEngine::Window::__surfaceDestroyed(void) {}

#endif