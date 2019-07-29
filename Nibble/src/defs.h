/**
 * @file defs.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains system information.
 * @version 0.1
 * @date 2019-05-31
 *
 */

#ifndef DEFS_H
#define DEFS_H

#include <string>

/********************
 *  OS Recognition
 ********************/

// OS NUMBERS
#define __OS_WIN64__ 1
#define __OS_WIN32__ 2
#define __OS_LINUX__ 3
#define __OS_APPLE__ 4
#define __OS_ANDROID__ 5
#define __OS_UNKNOWN__ 6

// OS String Names
#define __OS_STR_WIN64__ "Windows x64"
#define __OS_STR_WIN32__ "Windows x86"
#define __OS_STR_LINUX__ "Linux OS"
#define __OS_STR_APPLE__ "Apple OS"
#define __OS_STR_ANDROID__ "Android OS"
#define __OS_STR_UNKNOWN__ "Unkown OS"

// Detect OS
#if defined(_WIN32)
#if defined(_WIN64)
#define __OS__ __OS_WIN64__
#define __OS_STR__ __OS_STR_WIN64__
#else
#define __OS__ __OS_WIN32__
#define __OS_STR__ __OS_STR_WIN32__
#endif
#define __WINDOWS__
#define __DESKTOP__
#elif defined(__ANDROID__)
#define __OS__ __OS_ANDROID__
#define __OS_STR__ __OS_STR_ANDROID__
#elif defined(__APPLE__) || defined(__MACH__)
#define __OS__ __OS_APPLE__
#define __OS_STR__ __OS_STR_APPLE__
#define __DESKTOP__
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define __OS__ __OS_LINUX__
#define __OS_STR__ __OS_STR_LINUX__
#define __LINUX__
#define __DESKTOP__
#else
#define __OS__ __OS_UNKNOWN__
#define __OS_STR__ __OS_STR_UNKOWN__
#endif

/**
 * @brief Returns a string representation of the host system.
 *
 * @param id			The ID of the host system.
 * @return const char*	Representation of the host system.
 */
static const char* os_to_str(int id) {
    if (id == 1) {
        // windows64
        return __OS_STR_WIN64__;
    } else if (id == 2) {
        // windows32
        return __OS_STR_WIN32__;
    } else if (id == 3) {
        // linux
        return __OS_STR_LINUX__;
    } else if (id == 4) {
        // apple
        return __OS_STR_APPLE__;
    } else if (id == 5) {
        // android
        return __OS_STR_ANDROID__;
    } else
        // unkown
        return __OS_STR_UNKNOWN__;
}

#endif
