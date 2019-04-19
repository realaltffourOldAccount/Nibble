#ifndef UTILS_H
#define UTILS_H
#pragma once
#include <string>
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

#endif