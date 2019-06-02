#ifndef UTILS_H
#define UTILS_H
#pragma once
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#ifdef __ANDROID__
#define GLFM_INCLUDE_ES3
#include <glfm.h>
#define FILE_COMPAT_ANDROID_ACTIVITY glfmAndroidGetActivity()
#include <vendor/file_compat.h>
#endif

using namespace std;

/**
 * @brief Reads a file.
 *
 * @param file			The file path.
 * @return std::string	The file data.
 */
static std::string readFile(std::string file) {
	std::ifstream filestream;
	filestream.open(file);
	if (filestream.is_open() == false) {
		Log::error("Error Could not read file: " + file + ".");
	}

	std::stringstream ss;
	ss << filestream.rdbuf();
	filestream.close();

	return ss.str();
}

/**
 * @brief Returns a file size.
 *
 * @param filename					The file name.
 * @return std::ifstream::pos_type	The file size.
 */
static std::ifstream::pos_type filesize(const char* filename) {
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

/**
 * @brief Returns if a value is between a range.
 *
 * @param x			The value to check.
 * @param begin		The begining of the range.
 * @param end		The end of the range
 * @return true		The value is between the range.
 * @return false	The value is not between the range.
 */
static bool isInRange(int x, int begin, int end) {
	if (begin <= x <= end) return true;
	return false;
}

/**
 * @brief Returns if the character is capital.
 *
 * @param c			The Character.
 * @return true		The value is capital.
 * @return false	The value is not capital.
 */
static bool isCap(char c) {
	if (c >= 'A' || c <= 'Z') return true;
	return false;
}

/**
 * @brief Returns if the character is lower.
 *
 * @param c			The Character.
 * @return true		The value is lower.
 * @return false	The value is not lower.
 */
static bool isLower(char c) {
	if (c >= 'a' || c <= 'z') return true;
	return false;
}

/**
 * @brief Searches a string if it contains a specific character.
 *
 * @param str		The string to search.
 * @param c			The character to search for.
 * @return true		The character is present in the string.
 * @return false	The character is not present in the string.
 */
static bool isContain(string str, char c) {
	for (int i = 0; i < str.size(); i++)
		if (str[i] == c) return true;
	return false;
}

/**
 * @brief Searches a string if it contains an alphabet.
 *
 * @param str		The string to search.
 * @return true		The string contains an alphabet.
 * @return false	The string doesn't contain an alphabet.
 */
static bool isContainAlph(string str) {
	for (int i = 0; i < str.size(); i++)
		if (isalpha(str[i])) return true;
	return false;
}

/**
 * @brief Searches a string if it contains a digit.
 *
 * @param str		The string to search.
 * @return true		The string contains a digit.
 * @return false	The string doesn't contain a digit.
 */
static bool isContainDigit(string str) {
	for (int i = 0; i < str.size(); i++)
		if (isdigit(str[i])) return true;
	return false;
}

/**
 * @brief Splits a path.
 *
 * @param str							The string containing the file path to
 * split.
 * @param delimiters					The delimiters to split on.
 * @return std::vector<std::string>		The splits generated.
 */
static std::vector<std::string> splitpath(std::string str,
										  std::set<char> delimiters) {
	std::vector<std::string> result;

	char const* pch = str.c_str();
	char const* start = pch;
	for (; *pch; ++pch) {
		if (delimiters.find(*pch) != delimiters.end()) {
			if (start != pch) {
				std::string str(start, pch);
				result.push_back(str);
			} else {
				result.push_back("");
			}
			start = pch + 1;
		}
	}
	result.push_back(start);

	return result;
}

#endif