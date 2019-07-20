/**
 * @file error_macros.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains useful error macros.
 * @version 0.1
 * @date 2019-05-31
 *
 */

#ifndef ERROR_MACROS_h
#define ERROR_MACROS_h
#include "common.h"

/**
 * @brief  Checks for errors and terminates if an error has ocurred.
 *
 */
static void __err_proc(void) {
    // error occured
#if defined(__DEBUG__)
    Log::error("Error Occurred.",
            Log::GenLogID(__LINE__, __FILE__, "error", __func__));
    Log::warn("Info Logged to log/Log.txt",
            Log::GenLogID(__LINE__, __FILE__, "error", __func__));
#else
#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
    MessageBox(NULL,
            "Error Occurred. \n Info Logged "
            "to log/Log.txt",
            "Error", 0);
#elif (__OS__ == __OS_LINUX__)
    int res = system(
            "xmessage -center \"Error "
            "Occurred. \n Info Logged to "
            "log/Log.txt\"");
#endif
    // For other systems solution would be to make a glfw window, later TODO
#endif
#ifndef __WEBs__
    exit(EXIT_FAILURE);
#else
    emscripten_pause_main_loop();
#endif
}

/**
 * @brief Converts OpenGL error code to a string.
 *
 * @param err				The error to convert.
 * @return std::string		The string representation of that error.
 */
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
/**
 * @brief Clears any OpenGL pending errors by calling glGetError().
 *
 */
static void GLClearError() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

/**
 * @brief Reports any errors and calls @ref __err_check() if an error has
 * occured.
 *
 * @param line			The line number that caused the error.
 * @param func_name		The function name of the caller that caused the error.
 * @param file			The File caused the error.
 */
static void GLCheckError(int line, std::string func_name, std::string file) {
    GLenum err = glGetError();
    bool err_occ = false;
    while (err != GL_NO_ERROR) {
        Log::error("OpenGL Error Occured.",
                Log::GenLogID(__LINE__, __FILE__, "error", __func__));
        std::string error_name = err2str(err);

        Log::error("Error Type: " + error_name + ".",
                Log::GenLogID(__LINE__, __FILE__, "error", __func__));
        std::stringstream str;
        str << ("Error Occurred at: ");
        str << (func_name);
        str << ("@");
        str << (std::to_string(line));
        str << ("@");

        std::set<char> delims{'\\', '/'};
        std::vector<std::string> file_path = splitpath(file, delims);
        str << (file_path.back());
        Log::error(str.str(),
                Log::GenLogID(__LINE__, __FILE__, "error", __func__));
        err = glGetError();
        err_occ = true;
    }
    if (err_occ) __err_proc();
}

/**
 * @brief SHould be used to encapsulate any OpenGL Functions.
 *
 */
#define GLCall(x)   \
    GLClearError(); \
    x;              \
    GLCheckError(__LINE__, __func__, __FILE__)
// End GLCall

#endif
