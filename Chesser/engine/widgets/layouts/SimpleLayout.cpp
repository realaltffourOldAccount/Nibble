#include "SimpleLayout.h"

namespace GEngine {
namespace Widgets {
namespace Layouts {
SimpleLayout::SimpleLayout(void) {}
SimpleLayout::SimpleLayout(
	std::map<std::string, Drawables::Drawable*> drawables) {
	this->mDrawables = drawables;
}
SimpleLayout::SimpleLayout(
	Rect shape, std::map<std::string, Drawables::Drawable*> drawables)
	: Layout(shape) {
	this->mDrawables = drawables;
}
SimpleLayout::SimpleLayout(Rect shape) : Layout(shape) {}
SimpleLayout::~SimpleLayout(void) {}

bool SimpleLayout::eventHandler(Event* evt) {
	for (auto i = this->mDrawables.begin(); i != this->mDrawables.end(); i++) {
		if (i->second->eventHandler(evt)) return true;
	}
	return false;
}

void SimpleLayout::render(void) {
	glm::mat4 layout_mat = glm::translate(
		glm::mat4(1.0f), glm::vec3(this->mRect.x, this->mRect.y, 1.0f));
	for (auto i = this->mDrawables.begin(); i != this->mDrawables.end(); i++) {
		i->second->translate(glm::vec2(this->mRect.x, this->mRect.y));
		i->second->render();
		i->second->translate(glm::vec2(-this->mRect.x, -this->mRect.y));
	}
}
void SimpleLayout::tick(void) {
	for (auto i = this->mDrawables.begin(); i != this->mDrawables.end(); i++) {
		i->second->tick();
	}
}
}  // namespace Layouts
}  // namespace Widgets
}  // namespace GEngine