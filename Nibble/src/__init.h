/**
 * @file __init.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains basic initiliazation functions.
 * @version 0.1
 * @date 2019-05-31
 *
 */

#ifndef __INIT_H
#define __INIT_H

#include "common.h"
#include "error_macros.h"

#if !defined(__ANDROID__) 
/**
 * @brief The GLFW library callback.
 *
 * @param error			The error code.
 * @param description	The description of the error.
 */
static void glfw_error_callback(int error, const char* description) {
    Log::error("GLFW Error: ",
            Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
    Log::error("GLFW Error Code: " + std::to_string(error),
            Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
    Log::error("GLFW Error Desc: " + std::string(description),
            Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
}

/**
 * @brief Initializes the GLFW library.
 *
 */
static void initGLFW(void) { glfwSetErrorCallback(glfw_error_callback); }

/**
 * @brief Initializes the GLAD library.
 *
 */
static void initGLAD(void) {
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Log::info("GLAD Initialized.",
                Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
    } else {
        THROW_ERROR("GLAD Failed To Initialize.",
                Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
    }
}
/**
 * @brief Initializes all libraries.
 *
 * @param argc	The number of commands passed from the command line.
 * @param argv	The commands passed from the command line.
 */
static void initApp(int argc, char* argv[]) {
    Log::Init(argc, argv);
    Log::info("Detected OS: " + std::string(os_to_str(__OS__)),
            Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
#ifndef __ANDROID__
    initGLFW();
#endif
}

#endif
#endif
