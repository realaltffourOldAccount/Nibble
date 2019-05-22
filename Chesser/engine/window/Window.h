#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

#include <engine/Timer.h>

#include <engine/window/WindowBase.h>

#if defined(__DESKTOP__)
// Desktop
#include <engine/window/desktop/Window_desktop.h>
#elif defined(__WEB__)
// Emscripten
#include <engine/window/emscripten/Window_emscripten.h>
#elif defined(__ANDROID__)
// Android
#include <engine/window/android/Window_android.h>
#endif

#endif