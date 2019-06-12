/**
 * @file Layout.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief This contains the layout definition.
 * @version 0.1
 * @date 2019-06-04
 *
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <engine/events/events.h>
#include <engine/widgets/drawables/drawables.h>
#include "common.h"

namespace GEngine {
namespace Widgets {
namespace Layouts {
class Layout {
   public:
	Layout(void);
	Layout(Rect shape);
	~Layout(void);

	virtual void render(void) = 0;
	virtual void tick(void) = 0;

	virtual bool eventHandler(Event* evt) = 0;

	void setShape(Rect shape) { this->mRect = shape; }
	Rect getShape(void) { return this->mRect; }
	glm::mat4 getModel(void) { return this->mModel; }

	virtual void scale(glm::vec2 scale);
	virtual void transform(glm::vec2 trans);

   protected:
	Rect mRect;

	glm::mat4 mModel = glm::mat4(1.0f);
};  // namespace WidgetsclassLayout
}  // namespace Layouts
}  // namespace Widgets
}  // namespace GEngine
#endif