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
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Log {
#if !defined(__RELEASE__)
static std::shared_ptr<spdlog::logger> console;
#endif
static std::shared_ptr<spdlog::logger> file_log;

static void Init() {
// In Android there is no need for initializing the log because the android
// log library will do that for us.
#if !defined(__RELEASE__)
    console = spdlog::stdout_color_mt("Console");
#endif

#if !defined(__ANDROID__)
    std::ofstream log("Log.txt");
    log << "";
    log.close();

    file_log = spdlog::basic_logger_mt("File_Log", "Log.txt");
#endif
#if !defined(__RELEASE__)
    spdlog::get("Console")->set_pattern(
        "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
#endif
#if !defined(__ANDROID__)
    spdlog::get("File_Log")
        ->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
#endif
}

static void error(std::string msg) {
#if !defined(__RELEASE__)
    spdlog::get("Console")->error(msg.c_str());
#endif
#if !defined(__ANDROID__)
    spdlog::get("File_Log")->error(msg.c_str());
    spdlog::get("File_Log")->flush();
#endif
}

static void info(std::string msg) {
#if !defined(__RELEASE__)
    spdlog::get("Console")->info(msg.c_str());
#endif
#if !defined(__ANDROID__)
    spdlog::get("File_Log")->info(msg.c_str());
    spdlog::get("File_Log")->flush();
#endif
}

static void warn(std::string msg) {
#if !defined(__RELEASE__)
    spdlog::get("Console")->warn(msg.c_str());
#endif
#if !defined(__ANDROID__)
    spdlog::get("File_Log")->warn(msg.c_str());
    spdlog::get("File_Log")->flush();
#endif
}

static void trace(std::string msg) {
#if !defined(__RELEASE__)
    spdlog::get("Console")->trace(msg.c_str());
#endif
#if !defined(__ANDROID__)
    spdlog::get("File_Log")->trace(msg.c_str());
    spdlog::get("File_Log")->flush();
#endif
}
}; // namespace Log
#endif