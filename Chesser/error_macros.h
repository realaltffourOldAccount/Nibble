#ifndef ERROR_MACROS_h
#define ERROR_MACROS_h
#include "common.h"

static void __err_check(void) {
    // error occured
#if defined(__DEBUG__)
    Log::error("Error Occured.");
    Log::warn("Info Logged to log/Log.txt");
#else
#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
    MessageBox(NULL,
               "Error Occured. \n Info Logged "
               "to log/Log.txt",
               "Error", 0);
#elif (__OS__ == __OS_LINUX__)
    int res = system("xmessage -center \"Error "
                     "Occured. \n Info Logged to "
                     "log/Log.txt\"");
#endif
// For other systems solution would be to make a glfw window, later TODO
#endif
#ifndef __EMSCRIPTEN__
    exit(EXIT_FAILURE);
#else
    emscripten_pause_main_loop();
#endif
}

static std::string err2str(GLenum err) {
    switch (err) {
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
#ifndef __ANDROID__
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
        break;
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
        break;
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
        break;
    case GL_CONTEXT_LOST:
        return "GL_CONTEXT_LOST";
#endif
    }
    return "Unkown OpenGL Error";
}
static void GLClearError() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

static void GLCheckError(int line, std::string func_name, std::string file) {
    GLenum err = glGetError();
    bool err_occ = false;
    while (err != GL_NO_ERROR) {
        THROW_ERROR("OpenGL Error Occured.");
        std::string error_name = err2str(err);

        Log::error("Error Type: " + error_name + ".");
        std::stringstream str;
        str << ("Error Occured at: ");
        str << (std::to_string(line));
        str << ("@");
        str << (func_name);
        str << ("@");

        std::set<char> delims{'\\', '/'};
        std::vector<std::string> file_path = splitpath(file, delims);
        str << (file_path.back());
        Log::error(str.str());
        err = glGetError();
        err_occ = true;
    }
    if (err_occ)
        __err_check();
}

#define GLCall(x)                                                              \
    GLClearError();                                                            \
    x;                                                                         \
    GLCheckError(__LINE__, __func__, __FILE__)
// End GLCall

#endif