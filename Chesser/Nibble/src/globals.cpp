#include "globals.h"

bool g_engine_init = false;
bool g_opengl_init = false;
//int g_opengl_ver_major = 0;
//int g_opengl_ver_minor = 0;
//float g_glsl_version = 0.0f;

#ifdef __ANDROID__
GLFMDisplay* g_ADisplay = nullptr;
#endif
