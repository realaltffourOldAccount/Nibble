/**
 * @file globals.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Defines and declares global variables of the app.
 * @version 0.1
 * @date 2019-05-31
 *
 */

#ifndef GLOBALS_H
#define GLOBALS_H

extern bool g_engine_init;
extern bool g_opengl_init;
//extern int g_opengl_ver_major;
//extern int g_opengl_ver_minor;
//extern float g_glsl_version;

#ifdef __ANDROID__
#include <glfm.h>
extern GLFMDisplay* g_ADisplay;
#endif

#endif
