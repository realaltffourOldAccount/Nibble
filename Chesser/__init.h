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

#ifndef __ANDROID__
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
#ifndef __EMSCRIPTEN__
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log::info("GLAD Initialized.",
				  Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
	} else {
		THROW_ERROR("GLAD Failed To Initialize.",
					Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
	}
#endif
}
#endif

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

static float getGLSLVersion(int openglvMaj, int openglvMin) {
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
#elif defined(__WEB__)
	if (openglvMaj == 2 && openglvMin == 0) return 1.10;
	if (openglvMaj == 3 && openglvMin == 0) return 3.00;
#elif defined(__ANDROID__)
	if (openglvMaj == 2 && openglvMin == 0) return 1.00;
	if (openglvMaj == 3 && openglvMin == 0) return 3.00;
	if (openglvMaj == 3 && openglvMin == 1) return 3.10;

#endif

	return -1;
}

static void initGLVersion() {
	Log::info(
		"OpenGL Version: " + std::string((char*)(glGetString(GL_VERSION))),
		Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));

#if !defined(__ANDROID__)
	glGetIntegerv(GL_MAJOR_VERSION, &g_opengl_ver_major);
	glGetIntegerv(GL_MINOR_VERSION, &g_opengl_ver_minor);
#else
	if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES32) {
		g_opengl_ver_major = 3;
		g_opengl_ver_minor = 2;
	} else if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES31) {
		g_opengl_ver_major = 3;
		g_opengl_ver_minor = 1;
	} else if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderingAPIOpenGLES3) {
		g_opengl_ver_major = 3;
		g_opengl_ver_minor = 0;
	} else /* if (glfmGetRenderingAPI(g_ADisplay) == GLFMRenderAPIOpenGLES2)*/ {
		g_opengl_ver_major = 2;
		g_opengl_ver_minor = 0;
	}
#endif

	g_glsl_version = getGLSLVersion(g_opengl_ver_major, g_opengl_ver_minor);

	std::string glslver;
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << g_glsl_version;
	glslver = out.str();

	Log::info("GLSL Version: " + glslver,
			  Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));

	Log::info("OpenGL Vendor: " + std::string((char*)(glGetString(GL_VENDOR))),
			  Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
	Log::info(
		"OpenGL Renderer: " + std::string((char*)(glGetString(GL_RENDERER))),
		Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
}

#endif
