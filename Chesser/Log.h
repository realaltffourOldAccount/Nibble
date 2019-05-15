#ifndef LOG_H
#define LOG_H

#ifdef __ANDROID__
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...)                                                              \
    ((void)__android_log_print(ANDROID_LOG_INFO, "Chesser", __VA_ARGS__))
#define LOGW(...)                                                              \
    ((void)__android_log_print(ANDROID_LOG_WARN, "Chesser", __VA_ARGS__))

#endif

#include "defs.h"
#include <fstream>
#include <istream>
#include <ostream>
#ifndef __EMSCRIPTEN__
#ifdef __WINDOWS__
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <windows.h>
#endif
#include <gflags/gflags.h>
#include <glog/logging.h>
#endif

#include <iostream>

namespace Log {

static void Init(int argc, char* argv[]) {
// In Android there is no need for initializing the log because the android
// log library will do that for us.
#ifndef __EMSCRIPTEN__
    FLAGS_logtostderr = 1;
    FLAGS_log_dir = "log_dir";
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
#endif
}

static void error(std::string msg) {
#ifndef __EMSCRIPTEN__
    LOG(ERROR) << msg;
#else
    std::cout << msg << std::endl;
#endif
}

static void info(std::string msg) {
#ifndef __EMSCRIPTEN__
    LOG(INFO) << msg;
#else
    std::cout << msg << std::endl;
#endif
}

static void warn(std::string msg) {
#ifndef __EMSCRIPTEN__
    LOG(INFO) << msg;
#else
    std::cout << msg << std::endl;
#endif
}

static void trace(std::string msg) {
#ifndef __EMSCRIPTEN__
    LOG(INFO) << msg;
#else
    std::cout << msg << std::endl;
#endif
}
}; // namespace Log
#endif