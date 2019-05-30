#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

#include <engine/Timer.h>

namespace GEngine {
namespace Window {

const static int desiredTickRate = 128;
const int maxSkipFrames = 10;

struct WindowState {
	int _win_width, _win_height;
	int _mouse_pos_x, _mouse_pos_y;
	bool _isMouseIn = true;

	bool _paused = false;
	bool _loading = false;
};

class WindowBase {
   public:
	using EventCallbackFn = std::function<void(Event& e)>;

	void setEventHandler(const EventCallbackFn& callback);

	virtual void start(void) = 0;
	virtual void destroy(void) = 0;

	WindowState getState(void) const;
	MVP* getMVP(void) const;
	glm::mat4 getProj(void) const;

	long double getMSPF(void) const;
	long double getUT(void) const;

   public:  // Custom Events
	virtual void tick(void) = 0;
	virtual void render(void) = 0;

   protected:
	WindowBase(void);
	~WindowBase(void);

	WindowState _state;
	MVP* _mvp = nullptr;
	glm::mat4 _projection = glm::mat4(1.0f);

	EventCallbackFn EventCallback;

	Timer* timer = nullptr;
	long double mspf = 0.0;
	long double ut = 0.0;

   public:
	virtual void __init(int w, int h, std::string str) = 0;
	virtual void __loop(void) = 0;
	virtual void __iter(void);
	virtual void __underhood_tick(void);
	virtual void __update_mvp(void);
};
}  // namespace Window
}  // namespace GEngine
#endif