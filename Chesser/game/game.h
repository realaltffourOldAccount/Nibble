#ifndef GAME_H
#define GAME_H
#include "chsr_api.h"

struct GameState {
    // GLFW state
    int win_width;
    int win_height;
    bool mouse_in = false;
};

class Game {
   public:  // Interface
    void Init();
    void Start();

    GameState* mState = nullptr;

   public:  // GLFW Events
    void OnResize(int width, int height);
    void OnKey(int key, int scancode, int action, int mods);
    void OnMousePos(double xpos, double ypos);
    void OnCursorEntered();
    void OnCursorExit();
    void OnMouseButton(int button, int action, int mods);
    void OnGLFWError(int error, const char* desc);

   private:  // Private Vars
    GLFWwindow* mWindow = nullptr;

   private:  // Private Funcs
    void Tick();
    void Render();
    void __loop();
    void __err_check();
};

static void error_callback(int error, const char* description) {}

static void mouse_button_callback(GLFWwindow* window, int button, int action,
                                  int mods) {
    void* data = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(data);

    game->OnMouseButton(button, action, mods);
}

static void cursor_enter_callback(GLFWwindow* window, int entered) {
    void* data = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(data);

    if (entered)
        game->OnCursorEntered();
    else
        game->OnCursorExit();
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    void* data = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(data);
    game->OnMousePos(xpos, ypos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    void* data = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(data);
    game->OnKey(key, scancode, action, mods);
}
static void resize_callback(GLFWwindow* window, int width, int height) {
    void* data = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(data);
    game->OnResize(width, height);
}

#endif