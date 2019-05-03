#ifndef INITIATOR_H
#define INITIATOR_H
#include "univ_includes.h"
#include "macros.h"
#include "defs.h"

struct AppState {
    bool error = false;
};

static AppState *state = new AppState();

static void init_glfw() {
    if (!glfwInit()) {
        THROW_ERROR(state, "Failed GLFW Initialization.");
        return;
    } else
        Log::info("GLFW Initialized.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWIndowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwSwapInterval(1);
}

static void init_app() {
    Log::Init();
    init_glfw();
}

#endif