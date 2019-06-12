/**
 * @file common.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains common includes.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef COMMON_H
#define COMMON_H
#pragma once

/*
		OS Specific Includes
*/
#include "defs.h"
#if defined(__WINDOWS__)
#include <windows.h>
#elif defined(__LINUX__)
#include <unistd.h>
#endif

/*
		Deps Includes
*/

#if defined(__DESKTOP__)
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#if defined(__WEB__)
#include <GLES3/gl32.h>
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>
#endif

#if defined(__ANDROID__)
#define GLFM_INCLUDE_ES3
#include <glfm.h>
#define FILE_COMPAT_ANDROID_ACTIVITY glfmAndroidGetActivity()
#include <vendor/file_compat.h>
#endif

#if defined(__WINDOWS__)
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <windows.h>
#endif
#if !defined(__EMSCRIPTEN__)
#include <gflags/gflags.h>
#include <glog/logging.h>
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

/*
		Universal files
*/
#include "Log.h"
#include "globals.h"
#include "macros.h"
#include "utils/utils.h"

/*
		STL Includes
*/
#include <algorithm>
#include <deque>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include <fstream>
#include <istream>
#include <ostream>

#include <chrono>

// Include correct threads library.
#if !defined(__WINDOWS__)
#include <thread>
#else
//#include <vendor/threads/mingw.thread.h>
#include <thread>
#endif

/*
		Univ Definitions
*/

#endif