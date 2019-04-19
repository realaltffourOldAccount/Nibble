#include "game.h"
#include "Log.h"

void Game::Init() {
    mState = new GameState();

    if (!glfwInit()) {
        THROW_ERROR(this, "Failed GLFW Initialization.");
        return;
    } else
        Log::info("GLFW Initialized.");
    mState->error = true;
#ifdef __APPLE__
    glfwWIndowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    mWindow = glfwCreateWindow(800, 600, "Chesser", NULL, NULL);
    if (mWindow == NULL) {
        THROW_ERROR(this, "Failed Window Creation.");
        return;
    } else
        Log::info("Window Created.");

    glfwMakeContextCurrent(mWindow);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(mWindow, resize_callback);
    glfwSetKeyCallback(mWindow, key_callback);
    glfwSetCursorPosCallback(mWindow, cursor_pos_callback);
    glfwSetCursorEnterCallback(mWindow, cursor_enter_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        THROW_ERROR(this, "Failed GLAD Initialization.");
        return;
    } else
        Log::info("GLAD Initialized.");

    glfwSwapInterval(1);
}

void Game::Start() {
    // Start Loop thread
    std::thread loop(&Game::__loop, this);

    // Keep checking for errors on this thread.
    using namespace std::this_thread;
    using namespace std::chrono_literals;
    while (1) {
        std::this_thread::sleep_for(500ms);
        if (mState->error) {
            // error occured
            loop.join();
            glfwDestroyWindow(mWindow);

#if defined(__DEBUG__)
            Log::error("Error Occured.");
            Log::warn("Info Logged to log/Log.txt");
#else
#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
            MessageBox(NULL, L"Error Occured. \n Info Logged to log/Log.txt");
#elif (__OS__ == __OS_LINUX__)
            int res = system(
                "xmessage -center \"Error Occured. \n Info Logged to "
                "log/Log.txt\"");
#endif
// For other systems solution would be to make a glfw window, later TODO
#endif
            glfwTerminate();
            break;
        }
    }
}

void Game::__loop() {
    while (!glfwWindowShouldClose(mWindow)) {
        Render();
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        Tick();
    }
}

void Game::Tick() {}

void Game::Render() {}

void Game::OnGLFWError(int error, const char* description) {}
void Game::OnResize(int width, int height) {
    mState->win_width = width;
    mState->win_height = height;
}
void Game::OnKey(int key, int scancode, int action, int mods) {}
void Game::OnMousePos(double xpos, double ypos) {}
void Game::OnCursorEntered() { mState->mouse_in = true; }
void Game::OnCursorExit() { mState->mouse_in = false; }
void Game::OnMouseButton(int button, int action, int mods) {}