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
	this->_window = glfwCreateWindow(w, h, str.c_str(), NULL, NULL);
	if (this->_window == NULL) {
		THROW_ERROR("Failed Window Creation.",
					Log::GenLogID(__LINE__, __FILE__, "Window", __func__));
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

	// Set up blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up timer
	this->timer = new GEngine::Timer();

	glfwSwapInterval(1);

	g_engine_init = true;
	g_opengl_init = true;
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
		this->tick();
		accumulatedTime -= deltaUpdateInterval;
		nLoops++;
	}

	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	this->render();
	glfwSwapBuffers(this->_window);

	// Log::info("MSPF: " + std::to_string(this->mspf) +
	//		  ", UT: " + std::to_string(this->ut));
}
void Window::__underhood_tick(void) {}

void Window::OnResize(int width, int height) {
	this->_state._win_width = width;
	this->_state._win_height = height;
	this->__update_mvp();

	GEngine::WindowResizeEvent event(width, height);
	this->EventCallback(event);
}
void Window::OnMousePos(double xpos, double ypos) {
	this->_state._mouse_pos_x = xpos;
	this->_state._mouse_pos_y = ypos;

	GEngine::MouseMovedEvent event(xpos, ypos);
	this->EventCallback(event);
}
void Window::OnCursorEntered(void) {
	this->_state._isMouseIn = true;

	GEngine::MouseEnteredEvent event;
	this->EventCallback(event);
}
void Window::OnCursorExit(void) {
	this->_state._isMouseIn = false;

	GEngine::MouseExitedEvent event;
	this->EventCallback(event);
}

void Window::OnKey(int key, int scancode, int action, int mods) {
	switch (action) {
		case GLFW_PRESS: {
			GEngine::KeyPressedEvent event(key, 0);
			this->EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			GEngine::KeyReleasedEvent event(key);
			this->EventCallback(event);
			break;
		}
		case GLFW_REPEAT: {
			GEngine::KeyPressedEvent event(key, 1);
			this->EventCallback(event);
		}
	}
}
void Window::OnMouseButton(int button, int action, int mods) {
	switch (action) {
		case GLFW_PRESS: {
			GEngine::MouseButtonPressedEvent event(button);
			this->EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			GEngine::MouseButtonReleasedEvent event(button);
			this->EventCallback(event);
			break;
		}
	}
}
#endif
}  // namespace Window
}  // namespace GEngine