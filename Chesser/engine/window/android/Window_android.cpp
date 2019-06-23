#include "Window_android.h"

namespace GEngine {
namespace Window {
#if defined(__ANDROID__)
Window::Window(GLFMDisplay* display) {
	g_ADisplay = display;
	this->__init(display);
}
Window::~Window(void) { this->destroy(); }

void Window::start(void) {
	// Does nothing,
	// In android there can't be endless loops.
}

void Window::destroy(void) {
	// Does nothing.
	// In android surfaceDestroyed can replace this.
}

void Window::__init(GLFMDisplay* display) {
	this->_window = display;
	glfmSetDisplayConfig(display, GLFMRenderingAPIOpenGLES31,
						 GLFMColorFormatRGBA8888, GLFMDepthFormatNone,
						 GLFMStencilFormatNone, GLFMMultisampleNone);
	glfmSetUserData(display, this);
	glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);
	glfmSetSurfaceResizedFunc(display, onSurfaceResized);
	glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
	glfmSetMainLoopFunc(display, onFrame);
	glfmSetTouchFunc(display, onTouch);
	glfmSetKeyFunc(display, onKey);

	g_engine_init = true;
}
void Window::__iter(void) {
	if (g_opengl_init) {
		// Tick the Ticker.
		this->timer->tick();

		// Measure MSPF
		auto currentTime = std::chrono::high_resolution_clock::now();
		nbFrames++;
		if ((currentTime - lastTime) >= std::chrono::seconds(1)) {
			GEngine::TimerResolution precision = this->timer->GetPrecision();
			if (precision == GEngine::TimerResolution::milliseconds)
				this->mspf = this->timer->GetTicksPerSec() / (double)(nbFrames);
			else if (precision == GEngine::TimerResolution::microseconds)
				this->mspf =
					(this->timer->GetTicksPerSec() / (double)(nbFrames)) / 1000;
			else if (precision == GEngine::TimerResolution::nanoseconds)
				this->mspf =
					(this->timer->GetTicksPerSec() / (double)(nbFrames)) /
					1000000;
			nbFrames = 0;
			lastTime += std::chrono::seconds(1);
		}

		// Delta time
		long double deltaTime = this->timer->GetDeltaTick();

		// add delta time to accumulation
		accumulatedTime += deltaTime;

		// update
		nLoops = 0;
		while (accumulatedTime >= deltaUpdateInterval &&
			   nLoops < maxSkipFrames) {
			// Measure UT
			auto currentTime = std::chrono::high_resolution_clock::now();
			nbTicks++;
			if ((currentTime - lastTimeTick) >= std::chrono::seconds(1)) {
				GEngine::TimerResolution precision =
					this->timer->GetPrecision();
				if (precision == GEngine::TimerResolution::milliseconds)
					this->ut =
						this->timer->GetTicksPerSec() / (long double)(nbTicks);
				else if (precision == GEngine::TimerResolution::microseconds)
					this->ut = (this->timer->GetTicksPerSec() /
								(long double)(nbTicks)) /
							   1000;
				else if (precision == GEngine::TimerResolution::nanoseconds)
					this->ut = (this->timer->GetTicksPerSec() /
								(long double)(nbTicks)) /
							   1000000;
				nbTicks = 0;
				lastTimeTick += std::chrono::seconds(1);
			}

			// TODO: Check for correctness of location.
			this->HandleEvents();
			this->tick();
			accumulatedTime -= deltaUpdateInterval;
			nLoops++;
		}

		if (g_opengl_ver_major >= 3) {
			this->mFrameBuffer->bind();
			this->mFrameBuffer->clear();
			this->render();
			this->mFrameBuffer->unbind();

			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			this->mFrameBuffer->render();
		} else {
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			this->render();
		}

		// Sleep if more than needed fps
		long double leftOver =
			deltaFrameInterval - (this->timer->GetCurrent() -
								  std::chrono::high_resolution_clock::now())
									 .count();
		if (leftOver > 0.0) {
			if (this->timer->GetPrecision() ==
				GEngine::TimerResolution::microseconds)
				std::this_thread::sleep_for(
					std::chrono::microseconds((int)leftOver));
			else if (this->timer->GetPrecision() ==
					 GEngine::TimerResolution::milliseconds)
				std::this_thread::sleep_for(
					std::chrono::milliseconds((int)leftOver));
			else if (this->timer->GetPrecision() ==
					 GEngine::TimerResolution::nanoseconds)
				std::this_thread::sleep_for(
					std::chrono::nanoseconds((int)leftOver));
		}

		// Log::info("MSPF: " + std::to_string(this->mspf) +
		//		  ", UT: " + std::to_string(this->ut));
	}
}

void Window::OnSurfaceCreated(void) {
	Log::info("Surface Created",
			  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
	glfmGetDisplaySize(this->_window, &this->_state._win_width,
					   &this->_state._win_height);

	this->_mvp = new GEngine::MVP();
	this->__update_mvp();

	this->timer = new GEngine::Timer();
	this->timer->reset();

	this->deltaUpdateInterval = this->timer->GetTicksPerSec() / desiredTickRate;
	this->deltaFrameInterval = this->timer->GetTicksPerSec() / desiredFPS;
	this->lastTime = this->timer->GetStart();
	this->lastTimeTick = this->timer->GetStart();

	g_opengl_init = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initGLVersion();

	this->mFrameBuffer = new GEngine::FrameBuffer(
		this->_state._win_width, this->_state._win_height, true, true);

	this->init();
}
void Window::OnSurfaceDestroyed(void) {
	Log::info("Surface Destroyed",
			  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
}

void Window::OnSurfaceResized(GLFMDisplay* display, const int width,
							  const int height) {
	this->_state._win_width = width;
	this->_state._win_height = height;
	this->__update_mvp();

	GEngine::WindowResizeEvent* event =
		new GEngine::WindowResizeEvent(width, height);
	// this->EventCallback(event);
	this->mEventQueue.QueueEvent(event);
}

void Window::OnFrame(GLFMDisplay* display, const double frameTime) {
	this->__iter();
}

void Window::OnTouch(GLFMDisplay* display, int touch, GLFMTouchPhase phase,
					 double x, double y) {
	switch (phase) {
		case GLFMTouchPhaseBegan: {
			GEngine::TouchBeganEvent* event =
				new GEngine::TouchBeganEvent(x, y);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterTouchState(API_INPUT_ANDROID_TOUCH_BEGAN);
			this->mInput->RegisterTouchPosition(x, y);
			break;
		}
		case GLFMTouchPhaseMoved: {
			GEngine::TouchMovedEvent* event =
				new GEngine::TouchMovedEvent(x, y);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterTouchState(API_INPUT_ANDROID_TOUCH_MOVED);
			this->mInput->RegisterTouchPosition(x, y);
			break;
		}
		case GLFMTouchPhaseEnded: {
			GEngine::TouchEndedEvent* event =
				new GEngine::TouchEndedEvent(x, y);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterTouchState(API_INPUT_ANDROID_TOUCH_ENDED);
			this->mInput->RegisterTouchPosition(x, y);
			break;
		}
		case GLFMTouchPhaseCancelled: {
			GEngine::TouchCancelledEvent* event =
				new GEngine::TouchCancelledEvent(x, y);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterTouchState(API_INPUT_ANDROID_TOUCH_CANCELLED);
			this->mInput->RegisterTouchPosition(x, y);
			break;
		}
		case GLFMTouchPhaseHover: {
			GEngine::TouchHoverEvent* event =
				new GEngine::TouchHoverEvent(x, y);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterTouchState(API_INPUT_ANDROID_TOUCH_HOVER);
			this->mInput->RegisterTouchPosition(x, y);
			break;
		}
	}
}

void Window::OnKey(GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action,
				   int modifiers) {
	switch (action) {
		case GLFMKeyActionPressed: {
			GEngine::KeyPressedEvent* event =
				new GEngine::KeyPressedEvent(keyCode, 0);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			if (keyCode == GLFMKeyBackspace) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_BACKSPACE);
			} else if (keyCode == GLFMKeyTab) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_TAB);
			} else if (keyCode == GLFMKeyEnter) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_ENTER);
			} else if (keyCode == GLFMKeyEscape) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_ESCAPE);
			} else if (keyCode == GLFMKeySpace) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_SPACE);
			} else if (keyCode == GLFMKeyLeft) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_LEFT);
			} else if (keyCode == GLFMKeyRight) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_RIGHT);
			} else if (keyCode == GLFMKeyDown) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_DOWN);
			} else if (keyCode == GLFMKeyNavBack) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVBACK);
			} else if (keyCode == GLFMKeyNavMenu) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVMENU);
			} else if (keyCode == GLFMKeyNavSelect) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVSELECT);
			} else if (keyCode == GLFMKeyPlayPause) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_PLAYPAUSE);
			} else
				this->mInput->RegisterKey(keyCode);
			break;
		}
		case GLFMKeyActionReleased: {
			GEngine::KeyReleasedEvent* event =
				new GEngine::KeyReleasedEvent(keyCode);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			if (keyCode == GLFMKeyBackspace) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_BACKSPACE);
			} else if (keyCode == GLFMKeyTab) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_TAB);
			} else if (keyCode == GLFMKeyEnter) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_ENTER);
			} else if (keyCode == GLFMKeyEscape) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_ESCAPE);
			} else if (keyCode == GLFMKeySpace) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_SPACE);
			} else if (keyCode == GLFMKeyLeft) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_LEFT);
			} else if (keyCode == GLFMKeyRight) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_RIGHT);
			} else if (keyCode == GLFMKeyDown) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_DOWN);
			} else if (keyCode == GLFMKeyNavBack) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_NAVBACK);
			} else if (keyCode == GLFMKeyNavMenu) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_NAVMENU);
			} else if (keyCode == GLFMKeyNavSelect) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_NAVSELECT);
			} else if (keyCode == GLFMKeyPlayPause) {
				this->mInput->UnRegisterKey(API_INPUT_ANDROID_PLAYPAUSE);
			} else
				this->mInput->UnRegisterKey(keyCode);
			break;
		}
		case GLFMKeyActionRepeated: {
			GEngine::KeyPressedEvent* event =
				new GEngine::KeyPressedEvent(keyCode, 1);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			if (keyCode == GLFMKeyBackspace) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_BACKSPACE);
			} else if (keyCode == GLFMKeyTab) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_TAB);
			} else if (keyCode == GLFMKeyEnter) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_ENTER);
			} else if (keyCode == GLFMKeyEscape) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_ESCAPE);
			} else if (keyCode == GLFMKeySpace) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_SPACE);
			} else if (keyCode == GLFMKeyLeft) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_LEFT);
			} else if (keyCode == GLFMKeyRight) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_RIGHT);
			} else if (keyCode == GLFMKeyDown) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_DOWN);
			} else if (keyCode == GLFMKeyNavBack) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVBACK);
			} else if (keyCode == GLFMKeyNavMenu) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVMENU);
			} else if (keyCode == GLFMKeyNavSelect) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_NAVSELECT);
			} else if (keyCode == GLFMKeyPlayPause) {
				this->mInput->RegisterKey(API_INPUT_ANDROID_PLAYPAUSE);
			} else
				this->mInput->RegisterKey(keyCode);
			break;
		}
		default:
			break;
	}
}

#endif
}  // namespace Window
}  // namespace GEngine