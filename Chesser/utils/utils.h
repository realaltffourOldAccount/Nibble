#ifndef UTILS_H
#define UTILS_H
#pragma once
#include <set>
#include <string>
#include <vector>
using namespace std;

static bool isInRange(int x, int begin, int end) {
    if (begin <= x <= end)
        return true;
    return false;
}

static bool isCap(char c) {
    if (c >= 'A' || c <= 'Z')
        return true;
    return false;
}

static bool isLower(char c) {
    if (c >= 'a' || c <= 'z')
        return true;
    return false;
}

static bool isContain(string str, char c) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] == c)
            return true;
    return false;
}

static bool isContainAlph(string str) {
    for (int i = 0; i < str.size(); i++)
        if (isalpha(str[i]))
            return true;
    return false;
}

static bool isContainDigit(string str) {
    for (int i = 0; i < str.size(); i++)
        if (isdigit(str[i]))
            return true;
    return false;
}

static char getCharFromType(int type) {
    switch (type) {
    case 0:
        return 'K';
    case 1:
        return 'Q';
    case 2:
        return 'R';
    case 3:
        return 'B';
    case 4:
        return 'N';
    case 5:
        return 'P';
    default:
        return '*';
        break;
    }
}

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