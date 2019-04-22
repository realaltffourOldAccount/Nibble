#ifndef DEFS_H
#define DEFS_H

/********************
 *  OS Recognition
 ********************/
#define __OS_WIN64__ 1
#define __OS_WIN32__ 2
#define __OS_LINUX__ 3
#define __OS_APPLE__ 4
#define __OS_UNKNOWN__ 5

#if defined(_WIN32)
#ifdef defined(_WIN64)
#define __OS__ __OS_WIN64__
#else
#define __OS__ __OS_WIN32__
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#define __OS__ __OS_APPLE__
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define __OS__ __OS_LINUX__
#else
#define __OS__ __OS_UNKNOWN__
#endif

static const char* os_to_str(int id) {
    if (id == 1) {
        // windows64
        return "Windows x64";
    } else if (id == 2) {
        // windows32
        return "Windows x32";
    } else if (id == 3) {
        // linux
        return "Linux";
    } else if (id == 4) {
        // apple
        return "Apple";
    } else if (id == 5) {
        // unkown
        return "Unknown OS";
    }
    return "Unknown OS";
}

#endif