#include "Window_android.h"

namespace GEngine {
namespace Window {
#if defined(__ANDROID__)
Window::Window(GLFMDisplay* display) { this->__init(display); }
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
	glfmSetDisplayConfig(display, GLFMRenderingAPIOpenGLES3,
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

			this->tick();
			accumulatedTime -= deltaUpdateInterval;
			nLoops++;
		}

		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		this->render();

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
	Log::info("Surface Created");
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

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->init();
}
void Window::OnSurfaceDestroyed(void) { Log::info("Surface Destroyed"); }

void Window::OnSurfaceResized(GLFMDisplay* display, const int width,
							  const int height) {
	this->_state._win_width = width;
	this->_state._win_height = height;
	this->__update_mvp();

	GEngine::WindowResizeEvent event(width, height);
	this->EventCallback(event);
}

void Window::OnFrame(GLFMDisplay* display, const double frameTime) {
	this->__iter();
}

void Window::OnTouch(GLFMDisplay* display, int touch, GLFMTouchPhase phase,
					 double x, double y) {
	switch (phase) {
		case GLFMTouchPhaseBegan: {
			GEngine::TouchBeganEvent event(x, y);
			this->EventCallback(event);
			break;
		}
		case GLFMTouchPhaseMoved: {
			GEngine::TouchMovedEvent event(x, y);
			this->EventCallback(event);
			break;
		}
		case GLFMTouchPhaseEnded: {
			GEngine::TouchEndedEvent event(x, y);
			this->EventCallback(event);
			break;
		}
		case GLFMTouchPhaseCancelled: {
			GEngine::TouchCancelledEvent event(x, y);
			this->EventCallback(event);
			break;
		}
		case GLFMTouchPhaseHover: {
			GEngine::TouchHoverEvent event(x, y);
			this->EventCallback(event);
			break;
		}
	}
}

void Window::OnKey(GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action,
				   int modifiers) {
	switch (action) {
		case GLFMKeyActionPressed: {
			GEngine::KeyPressedEvent event(keyCode, 0);
			this->EventCallback(event);
			break;
		}
		case GLFMKeyActionReleased: {
			GEngine::KeyReleasedEvent event(keyCode);
			this->EventCallback(event);
			break;
		}
		case GLFMKeyActionRepeated: {
			GEngine::KeyPressedEvent event(keyCode, 1);
			this->EventCallback(event);
			break;
		}
		default:
			break;
	}
}

#endif
}  // namespace Window
}  // namespace GEngine