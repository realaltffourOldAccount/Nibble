#include "game.h"
#include "Log.h"
#include <thread>

void Game::Init() {
    if (!glfwInit()) {
        Log::error("Failed GLFW Initialization.");
        return;
    }
#ifdef __APPLE__
        glfwWIndowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    mWindow = glfwCreateWindow(800, 600, "Chesser", NULL, NULL);
    if (mWindow == NULL) {
        Log::error("Failed Window Creation.");
        glfwTerminate();
    }

    glfwMakeContextCurrent(mWindow);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetFramebufferSizeCallback(mWindow, resize_callback);
    glfwSetKeyCallback(mWindow, key_callback);
    glfwSetCursorPosCallback(mWindow,  cursor_pos_callback);
    glfwSetCursorEnterCallback(mWindow, cursor_enter_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Log::error("Failed GLAD Initialization.");
        return;
    }

    mState = new GameState();
}

void Game::Start() {
    // Start Loop thread
    std::thread loop(&Game::__loop, this);

    // Keep checking for errors on this thread.
    while (1) {
        if (mState->error) {
            // error occured

            loop.join();
            break;
        }
    }
}

void Game::__loop() {
    
}

void Game::Tick() {

}

void Game::Render() {

}

void Game::OnResize(int width, int height) {
    mState->win_width = width;
    mState->win_height = height;
}
void Game::OnKey(int key, int scancode, int action, int mods) {
    
}
void Game::OnMousePos(double xpos, double ypos) {
    
}
void Game::OnCursorEntered() {
    mState->mouse_in = true;
}
void Game::OnCursorExit() {
    mState->mouse_in = false;
}
void Game::OnMouseButton(int button, int action, int mods) {
    
}