#include "game.h"
#include "Log.h"

void Game::Init() {
  mState = new GameState();

  mWindow = glfwCreateWindow(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT, "Chesser", NULL, NULL);
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
  // Start Loop thread
   __loop();
}

void Game::__loop() {
  Log::info("Started Game Loop.");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (!glfwWindowShouldClose(mWindow)) {
    glClear(GL_COLOR_BUFFER_BIT);
    Render();
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
    Tick();
  }
}

void Game::Tick() { __err_check(); }


void Game::Render() {
  
}

void Game::__err_check() {
  // Check for opengl error
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    THROW_ERROR(state, "OpenGL Error Occured.");
    std::string error_name;
    switch (err) {
      case GL_INVALID_ENUM:
        error_name = "GL_INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        error_name = "GL_INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION:
        error_name = "GL_INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW:
        error_name = "GL_STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW:
        error_name = "GL_STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY:
        error_name = "GL_OUT_OF_MEMORY";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        error_name = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
      case GL_CONTEXT_LOST:
        error_name = "GL_CONTEXT_LOST";
    }
    Log::error("Error Type: " + error_name + ".");
  }

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
    MessageBox(NULL, "Error Occured. \n Info Logged to log/Log.txt", "Error",
               0);
#elif (__OS__ == __OS_LINUX__)
    int res = system("xmessage -center \"Error Occured. \n Info Logged to "
                     "log/Log.txt\"");
#endif
// For other systems solution would be to make a glfw window, later TODO
#endif
    exit(EXIT_FAILURE);
  }
}


void Game::OnGLFWError(int error, const char *description) {}
void Game::OnResize(int width, int height) {
  mState->win_width = width;
  mState->win_height = height;
}
void Game::OnKey(int key, int scancode, int action, int mods) {}
void Game::OnMousePos(double xpos, double ypos) {}
void Game::OnCursorEntered() { mState->mouse_in = true; }
void Game::OnCursorExit() { mState->mouse_in = false; }
void Game::OnMouseButton(int button, int action, int mods) {}
