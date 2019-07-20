#include "Window_desktop.h"

namespace GEngine {
    namespace Window {
        Window::Window(bool auto_size, int width, int height, std::string title) {
            if (auto_size) {
                const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

                this->__init(mode->width, mode->height, title);
            } else
                this->__init(width, height, title);
        }

        Window::~Window(void) { this->destroy(); }

        void Window::start(void) { this->__loop(); }

        void Window::destroy(void) { glfwDestroyWindow(this->_window); }

        void Window::__init(int w, int h, std::string str) {
            int res = glfwInit();
            if (res == GLFW_TRUE) {
                Log::info("GLFW Initialized.",
                        Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
            } else {
                THROW_ERROR("GLFW Failed To Initialize.",
                        Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
            }

            int major_ver = MAX_GL_VER_MAJOR;
            int minor_ver = MAX_GL_VER_MINOR;

            if (res == GLFW_TRUE) {
glfw_init:
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);

                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if (__OS__ == __OS_APPLE__)
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
#endif
            }
            // Create window
            this->_window = glfwCreateWindow(w, h, str.c_str(), NULL, NULL);
            if (this->_window == NULL) {
                if (major_ver < 2) {
                    THROW_ERROR("Failed Window Creation.",
                            Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
                    return;
                } else if (minor_ver == 0) {
                    minor_ver = 9;
                    major_ver--;
                } else {
                    minor_ver--;
                }
                Log::warn("Failed Window Creation. Retrying . . . ",
                        Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
                goto glfw_init;

                return;
            } else
                Log::info("Window Created.",
                        Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
            // Create Context
            glfwMakeContextCurrent(this->_window);
            initGLAD();
            setupConfig();
            // Set event listeners
            glfwSetWindowUserPointer(this->_window, this);

            glfwSetFramebufferSizeCallback(this->_window, resize_callback);
            glfwSetKeyCallback(this->_window, key_callback);
            glfwSetCursorPosCallback(this->_window, cursor_pos_callback);
            glfwSetCursorEnterCallback(this->_window, cursor_enter_callback);
            glfwSetMouseButtonCallback(this->_window, mouse_button_callback);

            // Set up state
            glfwGetFramebufferSize(this->_window, &(this->_state._win_width),
                    &(this->_state._win_height));

            // Set up mvp
            this->_mvp = new GEngine::MVP();
            this->__update_mvp();

            // Set up blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // Set up timer
            this->timer = new GEngine::Timer();

            glfwSwapInterval(0);

            g_opengl_init = true;

            this->mRenderer = new GEngine::Renderers::PingPongRenderer(this->_state._win_width, this->_state._win_height, true, true);
            g_engine_init = true;
        }
        void Window::__loop(void) {
            using namespace std::chrono;
            Log::info("Started Game Loop.",
                    Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

            this->timer->reset();

            const double deltaUpdateInterval =
                this->timer->GetTicksPerSec() / desiredTickRate;
            long double accumulatedTime = 0.0;
            int nLoops = 0;

            auto lastTime = this->timer->GetStart();
            int nbFrames = 0;

            auto lastTimeTick = this->timer->GetStart();
            int nbTicks = 0;

            const int desiredFPS = 60;
            const double deltaFrameInterval =
                this->timer->GetTicksPerSec() / desiredFPS;

            while (!glfwWindowShouldClose(this->_window)) {
                // Tick the Ticker.
                this->timer->tick();

                // Measure MSPF
                auto currentTime = std::chrono::high_resolution_clock::now();
                nbFrames++;
                if ((currentTime - lastTime) >= std::chrono::seconds(1)) {
                    GEngine::TimerResolution precision = this->timer->GetPrecision();
                    if (precision == GEngine::TimerResolution::milliseconds)
                        this->mspf = this->timer->GetTicksPerSec() / (double)(nbFrames);
                    else if (precision == GEngine::TimerResolution::microseconds)
                        this->mspf =
                            (this->timer->GetTicksPerSec() / (double)(nbFrames)) / 1000;
                    else if (precision == GEngine::TimerResolution::nanoseconds)
                        this->mspf =
                            (this->timer->GetTicksPerSec() / (double)(nbFrames)) /
                            1000000;
                    nbFrames = 0;
                    lastTime += std::chrono::seconds(1);
                }
                // Acquire Events
                glfwPollEvents();
                // Delta time
                long double deltaTime = this->timer->GetDeltaTick();

                // add delta time to accumulation
                accumulatedTime += deltaTime;

                // update
                nLoops = 0;
                while (accumulatedTime >= deltaUpdateInterval &&
                        nLoops < maxSkipFrames) {
                    // Measure UT
                    auto currentTime = std::chrono::high_resolution_clock::now();
                    nbTicks++;
                    if ((currentTime - lastTimeTick) >= std::chrono::seconds(1)) {
                        GEngine::TimerResolution precision =
                            this->timer->GetPrecision();
                        if (precision == GEngine::TimerResolution::milliseconds)
                            this->ut =
                                this->timer->GetTicksPerSec() / (long double)(nbTicks);
                        else if (precision == GEngine::TimerResolution::microseconds)
                            this->ut = (this->timer->GetTicksPerSec() /
                                    (long double)(nbTicks)) /
                                1000;
                        else if (precision == GEngine::TimerResolution::nanoseconds)
                            this->ut = (this->timer->GetTicksPerSec() /
                                    (long double)(nbTicks)) /
                                1000000;
                        nbTicks = 0;
                        lastTimeTick += std::chrono::seconds(1);
                    }

                    // TODO: Check for correctness of the location.
                    this->HandleEvents();
                    this->tick();
                    accumulatedTime -= deltaUpdateInterval;
                    nLoops++;
                }

                this->mRenderer->getSourceFB()->bind();
                this->mRenderer->getSourceFB()->clear();
                this->render();
                this->mRenderer->getSourceFB()->unbind();

                GLCall(glClear(GL_COLOR_BUFFER_BIT));
                this->mRenderer->render();
                glfwSwapBuffers(this->_window);

                // Sleep if more than needed fps
                long double leftOver =
                    deltaFrameInterval -
                    (this->timer->GetCurrent() - high_resolution_clock::now()).count();
                if (leftOver > 0.0) {
                    if (this->timer->GetPrecision() ==
                            GEngine::TimerResolution::microseconds)
                        std::this_thread::sleep_for(
                                std::chrono::microseconds((int)leftOver));
                    else if (this->timer->GetPrecision() ==
                            GEngine::TimerResolution::milliseconds)
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds((int)leftOver));
                    else if (this->timer->GetPrecision() ==
                            GEngine::TimerResolution::nanoseconds)
                        std::this_thread::sleep_for(
                                std::chrono::nanoseconds((int)leftOver));
                }

                // Log::info("MSPF: " + std::to_string(this->mspf) +
                //		  ", UT: " + std::to_string(this->ut));
            }
        }

        void Window::OnResize(int width, int height) {
            this->_state._win_width = width;
            this->_state._win_height = height;
            this->__update_mvp();

            GEngine::WindowResizeEvent* event =
                new GEngine::WindowResizeEvent(width, height);
            // this->EventCallback(event);
            this->mEventQueue.QueueEvent(event);
        }
        void Window::OnMousePos(double xpos, double ypos) {
            GEngine::MouseMovedEvent* event = new GEngine::MouseMovedEvent(xpos, ypos);
            // this->EventCallback(event);
            this->mEventQueue.QueueEvent(event);
            this->mInput->RegisterMousePosition((int)xpos, (int)ypos);
        }
        void Window::OnCursorEntered(void) {
            this->_state._isMouseIn = true;

            GEngine::MouseEnteredEvent* event = new GEngine::MouseEnteredEvent();
            // this->EventCallback(event);
            this->mEventQueue.QueueEvent(event);
        }
        void Window::OnCursorExit(void) {
            this->_state._isMouseIn = false;

            GEngine::MouseExitedEvent* event = new GEngine::MouseExitedEvent();
            // this->EventCallback(event);
            this->mEventQueue.QueueEvent(event);
        }

        void Window::OnKey(int key, int scancode, int action, int mods) {
            switch (action) {
                case GLFW_PRESS: {
                                     GEngine::KeyPressedEvent* event =
                                         new GEngine::KeyPressedEvent(key, 0);
                                     // this->EventCallback(event);
                                     this->mEventQueue.QueueEvent(event);
                                     this->mInput->RegisterKey(key);
                                     break;
                                 }
                case GLFW_RELEASE: {
                                       GEngine::KeyReleasedEvent* event =
                                           new GEngine::KeyReleasedEvent(key);
                                       // this->EventCallback(event);
                                       this->mEventQueue.QueueEvent(event);
                                       this->mInput->UnRegisterKey(key);
                                       break;
                                   }
                case GLFW_REPEAT: {
                                      GEngine::KeyPressedEvent* event =
                                          new GEngine::KeyPressedEvent(key, 1);
                                      // this->EventCallback(event);
                                      this->mEventQueue.QueueEvent(event);
                                      this->mInput->RegisterKey(key);
                                  }
            }
        }
        void Window::OnMouseButton(int button, int action, int mods) {
            switch (action) {
                case GLFW_PRESS: {
                                     GEngine::MouseButtonPressedEvent* event =
                                         new GEngine::MouseButtonPressedEvent(button);
                                     // this->EventCallback(event);
                                     this->mEventQueue.QueueEvent(event);
                                     this->mInput->RegisterMouseKey(button);
                                     break;
                                 }
                case GLFW_RELEASE: {
                                       GEngine::MouseButtonReleasedEvent* event =
                                           new GEngine::MouseButtonReleasedEvent(button);
                                       // this->EventCallback(event);
                                       this->mEventQueue.QueueEvent(event);
                                       this->mInput->UnRegisterMouseKey(button);
                                       break;
                                   }
            }
        }
    }  // namespace Window
}  // namespace GEngine
