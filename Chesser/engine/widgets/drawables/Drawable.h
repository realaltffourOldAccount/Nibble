/**
 * @file Drawable.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains the definition of a drawable object.
 * @version 0.1
 * @date 2019-06-05
 *
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"

#include <engine/Point.h>
#include <engine/Rect.h>
#include <engine/events/events.h>

namespace GEngine {
namespace Widgets {
namespace Drawables {
class Drawable {
   public:
	Drawable(void);
	Drawable(Rect shape);
	~Drawable(void);

	virtual void render(void) = 0;
	virtual void tick(void) = 0;
	virtual void destroy(void) = 0;

	virtual bool eventHandler(Event* evt) = 0;

	void setShape(Rect shape) { this->mRect = shape; }
	Rect getShape(void) { return this->mRect; }
	glm::mat4 getModel(void) { return this->mModel; }

	virtual void scale(glm::vec2 scale);
	virtual void translate(glm::vec2 trans);

   protected:
	Rect mRect;

	glm::mat4 mModel = glm::mat4(1.0f);
};
}  // namespace Drawables
}  // namespace Widgets
}  // namespace GEngine

#endif