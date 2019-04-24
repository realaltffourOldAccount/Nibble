#include "game.h"
#include "Log.h"

#include "../engine/textures.h"

void Game::Init() {
    mState = new GameState();

    mWindow = glfwCreateWindow(800, 600, "Chesser", NULL, NULL);
    if (mWindow == NULL) {
        THROW_ERROR(state, "Failed Window Creation.");
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

    // GLAD Initialization
    if (!gladLoadGL()) {
        THROW_ERROR(state, "Failed GLAD Initialization.");
        return;
    } else
        Log::info("GLAD Initialized.");
}

void Game::Start() {
    Textures::Texture* tex = Textures::create_texture("assets/board.png"); 
    // Start Loop thread
    __loop();
}

void Game::__loop() {
    Log::info("Started Game Loop.");
    while (!glfwWindowShouldClose(mWindow)) {
        Render();
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        Tick();
    }
}

void Game::__err_check() {
    // Keep checking for errors on this thread.
    using namespace std::this_thread;
    using namespace std::chrono_literals;
    if (state->error) {
        // error occured
        glfwDestroyWindow(mWindow);

#if defined(__DEBUG__)
        Log::error("Error Occured.");
        Log::warn("Info Logged to log/Log.txt");
#else
#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
        MessageBox(NULL, "Error Occured. \n Info Logged to log/Log.txt",
                   "Error", 0);
#elif (__OS__ == __OS_LINUX__)
        int res = system(
            "xmessage -center \"Error Occured. \n Info Logged to "
            "log/Log.txt\"");
#endif
// For other systems solution would be to make a glfw window, later TODO
#endif
        exit(EXIT_FAILURE);
    }
}

void Game::Tick() { __err_check(); }

void Game::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

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
