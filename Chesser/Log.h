/**
 * @file Log.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief The main logger of the app.
 * @version 0.1
 * @date 2019-05-31
 *
 */

#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <istream>
#include <ostream>
#include "config.h"
#include "defs.h"

#if defined(__WINDOWS__)
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <windows.h>
#endif
#if !defined(__EMSCRIPTEN__)
#include <gflags/gflags.h>
#include <glog/logging.h>
#endif

#include <iostream>

namespace Log {

/**
 * @brief Initializes log libraries
 *
 * @param argc	The number of commands passed from the command line.
 * @param argv	The commands passed from the command line.
 */
static void Init(int argc, char* argv[]) {
#if defined(__DESKTOP__)
	FLAGS_logtostderr = 1;
	FLAGS_log_dir = "log_dir";
	google::InitGoogleLogging(argv[0]);
	gflags::ParseCommandLineFlags(&argc, &argv, true);
#endif
}

/**
 * @brief Logs a message as an error.
 *
 * @param msg	The message to print.
 */
static inline void error(std::string msg) {
#ifndef SUPRESS_ERROR
#ifndef __EMSCRIPTEN__
	LOG(ERROR) << msg;
#else
	std::cout << msg << std::endl;
#endif
#endif
}

/**
 * @brief Logs a message as an error.
 *
 * @param msg	The message to print.
 */
static inline void info(std::string msg) {
#ifndef SUPRESS_INFO
#ifndef __EMSCRIPTEN__
	LOG(INFO) << msg;
#else
	std::cout << msg << std::endl;
#endif
#endif
}

/**
 * @brief Logs a message as a warning.
 *
 * @param msg	The message to print.
 */
static inline void warn(std::string msg) {
#ifndef SUPRESS_WARN
#ifndef __EMSCRIPTEN__
	LOG(WARNING) << msg;
#else
	std::cout << msg << std::endl;
#endif
#endif
}
};  // namespace Log
#endif