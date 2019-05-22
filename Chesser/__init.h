#ifndef __INIT_H
#define __INIT_H

#include "common.h"
#include "error_macros.h"

#ifndef __ANDROID__
static void error_callback(int error, const char* description) {}
static void initGLFW(void) {
	int res = glfwInit();

	if (res == GLFW_TRUE) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		Log::info("GLFW Initialized.");
	} else if (res == GLFW_FALSE) {
		THROW_ERROR("GLFW Failed To Initialize.");
	}

	glfwSetErrorCallback(error_callback);
}

static void initGLAD(void) {
#ifndef __EMSCRIPTEN__
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log::info("GLAD Initialized.");
	} else {
		THROW_ERROR("GLAD Failed To Initialize.");
	}
#endif
}
#endif

static void initApp(int argc, char* argv[]) {
	Log::Init(argc, argv);
	Log::info("Detected OS: " + std::string(os_to_str(__OS__)));
#ifndef __ANDROID__
	initGLFW();
#endif
}

#endif