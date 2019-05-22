#include "WindowBase.h"

namespace GEngine {
namespace Window {
void WindowBase::setEventHandler(const EventCallbackFn& callback) {
	this->EventCallback = callback;
}

WindowState WindowBase::getState(void) const { return this->_state; }
GEngine::MVP* WindowBase::getMVP(void) const { return this->_mvp; }
glm::mat4 WindowBase::getProj(void) const { return this->_projection; }

WindowBase::WindowBase(void) {}
WindowBase::~WindowBase(void) {}

void WindowBase::__iter(void) {
	// This might not be used since the __loop function repeats one
	// iteration of __iter function.
}

void WindowBase::__underhood_tick(void) {
	// This might not be used, there isn't a must need for doing
	// in-engine long sequential updates.
}

void WindowBase::__update_mvp(void) {
	// Might be overrided, though not needed.
	// Basic functionality already declared.
	this->_projection = glm::ortho(0.0f, float(this->_state._win_width), 0.0f,
								   float(this->_state._win_height));
	;
	this->_mvp->updateProj(this->_projection);
}

}  // namespace Window
}  // namespace GEngine