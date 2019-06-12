#include "Drawable.h"

namespace GEngine {
namespace Widgets {
namespace Drawables {
Drawable::Drawable(Rect shape) { this->mRect = shape; }
Drawable::Drawable() {}
Drawable::~Drawable() {}

void Drawable::scale(glm::vec2 scale) {
	this->mModel = glm::scale(this->mModel, glm::vec3(scale.x, scale.y, 1.0f));
}
void Drawable::translate(glm::vec2 trans) {
	this->mModel =
		glm::translate(this->mModel, glm::vec3(trans.x, trans.y, 0.0f));
}

}  // namespace Drawables
}  // namespace Widgets
}  // namespace GEngine