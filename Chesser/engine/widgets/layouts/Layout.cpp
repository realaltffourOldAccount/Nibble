#include "Layout.h"

namespace GEngine {
namespace Widgets {
namespace Layouts {

Layout::Layout(void) {}
Layout::Layout(Rect shape) { this->mRect = shape; }
Layout::~Layout(void) {}

void Layout::scale(glm::vec2 scale) {
	this->mModel = glm::scale(this->mModel, glm::vec3(scale.x, scale.y, 1.0f));
}

void Layout::transform(glm::vec2 trans) {
	this->mModel =
		glm::translate(this->mModel, glm::vec3(trans.x, trans.y, 1.0f));
}

}  // namespace Layouts
}  // namespace Widgets
}  // namespace GEngine