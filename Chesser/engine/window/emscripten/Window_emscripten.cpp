#include "Window_emscripten.h"

namespace GEngine {
namespace Window {
#if defined(__WEB__)
Window::Window(bool auto_size, int width, int height, std::string title) {
	this->__init(width, height, title);
}
Window::~Window(void) { this->destroy(); }

Window* ptr = nullptr;
static void em__loop(void) { ptr->__iter(); }

void Window::start(void) {
	Log::info("Started Game Loop.",
			  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
	ptr = this;

	this->timer->reset();
	this->deltaUpdateInterval = this->timer->GetTicksPerSec() / desiredTickRate;
	this->deltaFrameInterval = this->timer->GetTicksPerSec() / this->desiredFPS;
	this->lastTime = this->timer->GetStart();
	this->lastTimeTick = this->timer->GetStart();

	emscripten_set_main_loop(em__loop, 0, 1);
}
void Window::destroy(void) {}

void Window::__init(int w, int h, std::string str) {
	int res = glfwInit();
	if (res == GLFW_TRUE) {
		Log::info("GLFW Initialized.",
				  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
	} else {
		THROW_ERROR("GLFW Failed To Initialize.",
					Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
	}

	int major_ver = MAX_GL_VER_MAJOR;
	int minor_ver = MAX_GL_VER_MINOR;

	if (res == GLFW_TRUE) {
	glfw_init:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	// Create window
	this->_window = glfwCreateWindow(w, h, str.c_str(), NULL, NULL);
	if (this->_window == NULL) {
		if (major_ver < 2) {
			THROW_ERROR("Failed Window Creation.",
						Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
			return;
		} else if (minor_ver == 0) {
			minor_ver = 9;
			major_ver--;
		} else {
			minor_ver--;
		}
		Log::warn("Failed Window Creation. Retrying . . . ",
				  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
		goto glfw_init;
		return;
	} else
		Log::info("Window Created.",
				  Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
	// Create Context
	glfwMakeContextCurrent(this->_window);
	initGLAD();
	// Set event listeners
	glfwSetWindowUserPointer(this->_window, this);

	glfwSetFramebufferSizeCallback(this->_window, resize_callback);
	glfwSetKeyCallback(this->_window, key_callback);
	glfwSetCursorPosCallback(this->_window, cursor_pos_callback);
	glfwSetCursorEnterCallback(this->_window, cursor_enter_callback);
	glfwSetMouseButtonCallback(this->_window, mouse_button_callback);

	// Set up state
	glfwGetFramebufferSize(this->_window, &(this->_state._win_width),
						   &(this->_state._win_height));

	// Set up mvp
	this->_mvp = new GEngine::MVP();
	this->__update_mvp();

	// Set up timer
	this->timer = new GEngine::Timer();

	glfwSwapInterval(1);

	g_opengl_init = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initGLVersion();

	this->mFrameBuffer = new GEngine::FrameBuffer(
		this->_state._win_width, this->_state._win_height, false, false);

	g_engine_init = true;
}
void Window::__iter(void) {
	// Tick the timer.
	this->timer->tick();

	// Measure MSPF
	auto currentTime = std::chrono::high_resolution_clock::now();
	this->nbFrames++;
	if ((currentTime - lastTime) >= std::chrono::seconds(1)) {
		GEngine::TimerResolution precision = this->timer->GetPrecision();
		if (precision == GEngine::TimerResolution::milliseconds)
			this->mspf = this->timer->GetTicksPerSec() / (double)(nbFrames);
		else if (precision == GEngine::TimerResolution::microseconds)
			this->mspf =
				(this->timer->GetTicksPerSec() / (double)(nbFrames)) / 1000;
		else if (precision == GEngine::TimerResolution::nanoseconds)
			this->mspf =
				(this->timer->GetTicksPerSec() / (double)(nbFrames)) / 1000000;
		this->nbFrames = 0;
		this->lastTime += std::chrono::seconds(1);
	}
	// Acquire Events
	glfwPollEvents();

	// Delta time
	long double deltaTime = this->timer->GetDeltaTick();

	// add delta time to accumulation
	this->accumulatedTime += deltaTime;

	// update
	nLoops = 0;
	while (this->accumulatedTime >= deltaUpdateInterval &&
		   nLoops < maxSkipFrames) {
		// Measure UT
		auto currentTime = std::chrono::high_resolution_clock::now();
		this->nbTicks++;
		if ((currentTime - this->lastTimeTick) >= std::chrono::seconds(1)) {
			GEngine::TimerResolution precision = this->timer->GetPrecision();
			if (precision == GEngine::TimerResolution::milliseconds)
				this->ut = this->timer->GetTicksPerSec() /
						   (long double)(this->nbTicks);
			else if (precision == GEngine::TimerResolution::microseconds)
				this->ut = (this->timer->GetTicksPerSec() /
							(long double)(this->nbTicks)) /
						   1000;
			else if (precision == GEngine::TimerResolution::nanoseconds)
				this->ut = (this->timer->GetTicksPerSec() /
							(long double)(this->nbTicks)) /
						   1000000;
			this->nbTicks = 0;
			this->lastTimeTick += std::chrono::seconds(1);
		}
		// TODO: Check for the correctness of the location.
		this->HandleEvents();
		this->tick();
		accumulatedTime -= deltaUpdateInterval;
		nLoops++;
	}

	this->mFrameBuffer->bind();
	this->mFrameBuffer->clear();
	this->render();
	this->mFrameBuffer->unbind();

	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	this->mFrameBuffer->render();
	glfwSwapBuffers(this->_window);

	// Log::info("MSPF: " + std::to_string(this->mspf) +
	//		  ", UT: " + std::to_string(this->ut));
}
void Window::__underhood_tick(void) {}

void Window::OnResize(int width, int height) {
	this->_state._win_width = width;
	this->_state._win_height = height;
	this->__update_mvp();

	GEngine::WindowResizeEvent* event =
		new GEngine::WindowResizeEvent(width, height);
	// this->EventCallback(event);
	this->mEventQueue.QueueEvent(event);
}
void Window::OnMousePos(double xpos, double ypos) {
	GEngine::MouseMovedEvent* event = new GEngine::MouseMovedEvent(xpos, ypos);
	// this->EventCallback(event);
	this->mEventQueue.QueueEvent(event);
	this->mInput->RegisterMousePosition(xpos, ypos);
}
void Window::OnCursorEntered(void) {
	this->_state._isMouseIn = true;

	GEngine::MouseEnteredEvent* event = new GEngine::MouseEnteredEvent;
	// this->EventCallback(event);
	this->mEventQueue.QueueEvent(event);
}
void Window::OnCursorExit(void) {
	this->_state._isMouseIn = false;

	GEngine::MouseExitedEvent* event = new GEngine::MouseExitedEvent;
	// this->EventCallback(event);
	this->mEventQueue.QueueEvent(event);
}

void Window::OnKey(int key, int scancode, int action, int mods) {
	switch (action) {
		case GLFW_PRESS: {
			GEngine::KeyPressedEvent* event =
				new GEngine::KeyPressedEvent(key, 0);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterKey(key);
			break;
		}
		case GLFW_RELEASE: {
			GEngine::KeyReleasedEvent* event =
				new GEngine::KeyReleasedEvent(key);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->UnRegisterKey(key);
			break;
		}
		case GLFW_REPEAT: {
			GEngine::KeyPressedEvent* event =
				new GEngine::KeyPressedEvent(key, 1);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterKey(key);
		}
	}
}
void Window::OnMouseButton(int button, int action, int mods) {
	switch (action) {
		case GLFW_PRESS: {
			GEngine::MouseButtonPressedEvent* event =
				new GEngine::MouseButtonPressedEvent(button);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->RegisterMouseKey(button);
			break;
		}
		case GLFW_RELEASE: {
			GEngine::MouseButtonReleasedEvent* event =
				new GEngine::MouseButtonReleasedEvent(button);
			// this->EventCallback(event);
			this->mEventQueue.QueueEvent(event);
			this->mInput->UnRegisterMouseKey(button);
			break;
		}
	}
}
#endif
}  // namespace Window
}  // namespace GEngine