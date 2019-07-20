/**
 * @file Window.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contain the real definition/include of the target os window class.
 * @version 0.1
 * @date 2019-05-31
 *
 */
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
#elif defined(__ANDROID__)
// Android
#include <engine/window/android/Window_android.h>
#endif

#endif
