/**
 * @file Log.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief The main logger of the app.
 * @version 0.2
 * @date 2019-05-31
 *
 */

#ifndef LOG_H
#define LOG_H
#pragma once

#include <utils/utils.h>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include "config.h"
#include "defs.h"

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
 * @brief Holds the list of messages.
 *
 */
extern vector<std::string>* g_log;

/**
 * @brief Holds the log file stream.
 *
 */
static std::ofstream g_logstream;

/**
 * @brief Flushes @ref g_log to Log.txt
 *
 */
static void FlushLog(void) {
	g_logstream.open("log.txt");
	if (g_logstream.is_open()) {
		for (int i = 0; i < g_log->size(); i++) {
			g_logstream << (*g_log)[i] << std::endl;
		}
		// g_logstream.flush();
		// LOG(INFO) << "Flushed Log.";
	} else {
#ifndef __WEB__
		LOG(WARNING) << "Did not flush Log, stream.is_open() failed.";
#else
		std::cout << "Did not flush Log, stream.is_open() failed." << std::endl;
#endif
	}
	g_logstream.close();
}

/**
 * @brief Logs a message as an error.
 *
 * @param msg	The message to print.
 */
static void error(std::string msg, std::string id) {
#ifndef SUPPRESS_ERROR
#ifndef __EMSCRIPTEN__
	LOG(ERROR) << id << msg;
#else
	std::cout << id << msg << std::endl;
#endif
#endif
	g_log->push_back(id + msg);
	Log::FlushLog();
}

/**
 * @brief Logs a message as an error.
 *
 * @param msg	The message to print.
 */
static void info(std::string msg, std::string id) {
#ifndef SUPPRESS_INFO
#ifndef __EMSCRIPTEN__
	LOG(INFO) << id << msg;
#else
	std::cout << id << msg << std::endl;
#endif
#endif
	g_log->push_back(id + msg);
	Log::FlushLog();
}

/**
 * @brief Logs a message as a warning.
 *
 * @param msg	The message to print.
 */
static void warn(std::string msg, std::string id) {
#ifndef SUPPRESS_WARNING
#ifndef __EMSCRIPTEN__
	LOG(WARNING) << id << msg;
#else
	std::cout << id << msg << std::endl;
#endif
#endif
	g_log->push_back(id + msg);
	Log::FlushLog();
}

/**
 * @brief Generates a log ID.
 *
 * @param line				The line number.
 * @param file_n			The file name.
 * @param class_n			The class name.
 * @param func				The function name.
 * @return std::string		The ID generated.
 */
static std::string GenLogID(int line, std::string file_n, std::string class_n,
							std::string func) {
	std::string id;
	id += "[ ";

	std::set<char> delims{'\\', '/'};
	std::vector<std::string> file_path = splitpath(file_n, delims);

	id += file_path.back() + "@";
	id += class_n + "@";
	id += func + "@";
	id += std::to_string(line);
	id += " ] ";

	return id;
}

/**
 * @brief Initializes log libraries
 *
 * @param argc	The number of commands passed from the command line.
 * @param argv	The commands passed from the command line.
 */
static void Init(int argc, char* argv[]) {
#if defined(__DESKTOP__)
	FLAGS_logtostderr = 1;
	google::InitGoogleLogging(argv[0]);
	gflags::ParseCommandLineFlags(&argc, &argv, true);
#endif
	g_logstream.open("log.txt");
	if (!g_logstream.is_open()) {
		Log::error("Could not make Log stream.",
				   Log::GenLogID(__LINE__, __FILE__, "Log", __func__));
	}
	g_logstream.close();
}

static inline void DeInit(void) { g_logstream.close(); }
};  // namespace Log
#endif