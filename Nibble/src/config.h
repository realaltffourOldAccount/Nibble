/**
 * @file config.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief
 * @version 0.2
 * @date 2019-06-01
 *
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "Log.h"
#include "common.h"

///////////////////////////////////////////
/**
 * @brief Suppresses all messages.
 *
 */
//#define SUPPRESS_ALL
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Unsuppresses all except for warning, info, error defines.
 *
 */
#define UNSUPPRESS_ALL
///////////////////////////////////////////

///////////////////////////////////////////
// Check if Unsuppress_all and Suppress_all both enabled.
#if defined(UNSUPPRESS_ALL) && defined(SUPPRESS_ALL)
#error "Can't Define UNSUPPRESS_ALL and SUPPRESS_ALL at the same time."
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Warnings from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_WARNING
#else
//#define SUPPRESS_WARNING  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Info from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_INFO
#else
//#define SUPPRESS_INFO  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Errors from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_ERROR
#else
//#define SUPPRESS_ERROR  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Event Logging. Currently has no effect.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_EVENTS
#else
#define SUPPRESS_EVENTS  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Files Successfully read messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_FILE_SUCCESS
#else
//#define SUPPRESS_FILE_SUCCESS  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Shader Successfully created messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_SHADER_SUCCESS
#else
//#define SUPPRESS_SHADER_SUCCESS  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Textures Successfully created messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_TEXTURE_SUCCESS
#else
//#define SUPPRESS_TEXTURE_SUCCESS  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Supresses Textures null warning messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_TEXTURE_NULL_WARNING
#else
//#define SUPPRESS_TEXTURE_NULL_WARNING  // Change this option.
#endif
///////////////////////////////////////////

///////////////////////////////////////////
/**
 * @brief Holds the configuration of the host.
 */
struct Config {
    ///////////////////////////////////////
    // Version Configuration.
    //
    int _openglvMajor = 0; // OpenGL Version Major.
    int _openglvMinor = 0; // OpenGL Version Minor.

    float _glsl_version = 0.0; // GLSL Version.
    ///////////////////////////////////////

    ///////////////////////////////////////
    // Feature Confguration.
    //
    bool _coreframeBufferSupport = false; // Frame Buffer Support.
    bool _corevertexArraySupport = false; // Vertex Array Support.
    bool _corerenderBufferSupport = false; // Render Buffer Support.

    bool _ARBframeBufferSupport = false; // Frame Buffer ARB Support.
    bool _ARBvertexArraySupport = false; // Vertex Array ARB Support.
    bool _ARBrenderBufferSupport = false; // Render Buffer ARB Support.

    bool _EXTframeBufferSupport = false; // Frame Buffer EXT Support.
    bool _EXTvertexArraySupport = false; // Vertex Array EXT Support.
    bool _EXTrenderBufferSupport = false; // Render Buffer EXT Support.

    bool _ARBnpot = false; // non-power of two Textures Support.

    ///////////////////////////////////////
};
extern Config* g_config;

static void initGLVersion(); 

static void printConfig() {
    Log::info("Configuration Setup: ", Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_coreframeBufferSupport="+std::to_string(g_config->_coreframeBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_corevertexArraySupport="+std::to_string(g_config->_corevertexArraySupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_corerenderBufferSupport="+std::to_string(g_config->_corerenderBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));

    Log::info("_ARBframeBufferSupport="+std::to_string(g_config->_ARBframeBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_ARBvertexArraySupport="+std::to_string(g_config->_ARBvertexArraySupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_ARBrenderBufferSupport="+std::to_string(g_config->_ARBrenderBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));

    Log::info("_EXTframeBufferSupport="+std::to_string(g_config->_EXTframeBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_EXTvertexArraySupport="+std::to_string(g_config->_EXTvertexArraySupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info("_EXTrenderBufferSupport="+std::to_string(g_config->_EXTrenderBufferSupport), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));

    Log::info("_ARBnpot="+std::to_string(g_config->_ARBnpot), Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
}

static void setupConfig() {
    initGLVersion();

#if !defined(__ANDROID__)
    if (g_config->_openglvMajor >= 3) {
        g_config->_coreframeBufferSupport = true;
        g_config->_corevertexArraySupport = true;
        g_config->_corerenderBufferSupport = true;
    }
    else {
        if (GL_ARB_framebuffer_object) {
            g_config->_ARBframeBufferSupport = true;
            g_config->_ARBrenderBufferSupport = true;
        }
        if (GL_ARB_vertex_array_object) {
            g_config->_ARBvertexArraySupport = true;
        }

        if (GL_EXT_framebuffer_object) {
            g_config->_EXTframeBufferSupport = true;
            g_config->_EXTrenderBufferSupport = true;
        }
        if (GL_EXT_vertex_array) {
            g_config->_EXTvertexArraySupport = true;
        }
    }

    if (GL_ARB_texture_non_power_of_two) {
        g_config->_ARBnpot = true;
    }
#elif defined(__ANDROID__)
    if (GL_OES_framebuffer_object) 
    {}
#endif

    printConfig();
}

static float getGLSLVersion(int openglvMaj, int openglvMin) {
    ///////////////////////////////////////
    // Get the GLSL Version based on the OpenGL Version.
#if defined(__DESKTOP__)
    if (openglvMaj >= 3 && openglvMin >= 3) {
        return openglvMaj + float(openglvMin / 10);
    } else {
        if (openglvMaj == 2 && openglvMin == 0) return 1.10;
        if (openglvMaj == 2 && openglvMin == 1) return 1.20;
        if (openglvMaj == 3 && openglvMin == 0) return 1.30;
        if (openglvMaj == 3 && openglvMin == 1) return 1.40;
        if (openglvMaj == 3 && openglvMin == 2) return 1.50;
    }
#elif defined(__ANDROID__)
    if (openglvMaj == 2 && openglvMin == 0) return 1.00;
    if (openglvMaj == 3 && openglvMin == 0) return 3.00;
    if (openglvMaj == 3 && openglvMin == 1) return 3.10;

#endif
    ///////////////////////////////////////

    return -1;
}

void initGLVersion() {
    ///////////////////////////////////////
    // Output Provided String representation of the OpenGL version.
    Log::info(
            "OpenGL Version: " + std::string((char*)(glGetString(GL_VERSION))),
            Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    ///////////////////////////////////////

    ///////////////////////////////////////
    // Get the number representation of the OpenGL Version.
#if !defined(__ANDROID__)
    glGetIntegerv(GL_MAJOR_VERSION, &g_config->_openglvMajor);
    glGetIntegerv(GL_MINOR_VERSION, &g_config->_openglvMinor);
#else
    if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES32) {
        g_config->_openglvMajor = 3;
        g_config->_openglvMinor = 2;
    } else if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES31) {
        g_config->_openglvMajor = 3;
        g_config->_openglvMinor = 1;
    } else if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES3) {
        g_config->_openglvMajor = 3;
        g_config->_openglvMinor = 0;
    } else /* if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderAPIOpenGLES2)*/ {
        g_config->_openglvMajor = 2;
        g_config->_openglvMinor = 0;
    }
#endif
    ///////////////////////////////////////

    ///////////////////////////////////////
    // Get the number representation of the GLSL Version.
    g_config->_glsl_version = getGLSLVersion(g_config->_openglvMajor, g_config->_openglvMinor);

    std::string glslver;
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << g_config->_glsl_version;
    glslver = out.str();
    ///////////////////////////////////////

    ///////////////////////////////////////
    // Output the GLSL Version, OpenGL Vendor, OpenGL Renderer.
    Log::info("GLSL Version: " + glslver,
            Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));

    Log::info("OpenGL Vendor: " + std::string((char*)(glGetString(GL_VENDOR))),
            Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    Log::info(
            "OpenGL Renderer: " + std::string((char*)(glGetString(GL_RENDERER))),
            Log::GenLogID(__LINE__, __FILE__, "Configuration", __func__));
    ///////////////////////////////////////
}

///////////////////////////////////////////

#endif
