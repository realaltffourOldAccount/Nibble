#ifndef LOG_H
#define LOG_H
#include "defs.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <fstream>
#include <istream>
#include <ostream>

namespace Log {
#ifndef __RELEASE__
static std::shared_ptr<spdlog::logger> console;
#endif
static std::shared_ptr<spdlog::logger> file_log;

static void Init() {
#ifndef __RELEASE__
    console = spdlog::stdout_color_mt("Console");
#endif
    std::ofstream log("Log.txt");
    log << "";
    log.close();

    file_log = spdlog::basic_logger_mt("File_Log", "Log.txt");
#ifndef __RELEASE__
    spdlog::get("Console")->set_pattern(
        "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
#endif
    spdlog::get("File_Log")
        ->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
}

static void error(std::string msg) {
#ifndef __RELEASE__
    spdlog::get("Console")->error(msg.c_str());
#endif
    spdlog::get("File_Log")->error(msg.c_str());
    spdlog::get("File_Log")->flush();
}

static void info(std::string msg) {
#ifndef __RELEASE__
    spdlog::get("Console")->info(msg.c_str());
#endif
    spdlog::get("File_Log")->info(msg.c_str());
    spdlog::get("File_Log")->flush();
}

static void warn(std::string msg) {
#ifndef __RELEASE__
    spdlog::get("Console")->warn(msg.c_str());
#endif
    spdlog::get("File_Log")->warn(msg.c_str());
    spdlog::get("File_Log")->flush();
}

static void trace(std::string msg) {
#ifndef __RELEASE__
    spdlog::get("Console")->trace(msg.c_str());
#endif
    spdlog::get("File_Log")->trace(msg.c_str());
    spdlog::get("File_Log")->flush();
}
};  // namespace Log
#endif