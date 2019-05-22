#ifndef MVP_H
#define MVP_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
class MVP {
   public:
	MVP(glm::mat4 model = glm::mat4(1.0f), glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 proj = glm::mat4(1.0f));
	~MVP(void);

	// This assumes that the shader program is binded,
	// beforehand.
	void bind(GLuint program);

	void updateModel(const glm::mat4 model);
	void updateView(const glm::mat4 view);
	void updateProj(const glm::mat4 proj);

	glm::mat4 getModel(void) const;
	glm::mat4 getView(void) const;
	glm::mat4 getProj(void) const;

	// This is not to be used often,
	// since it recalculates the mvp everytime.
	glm::mat4 getMVP(void);

	void destroy(void);

   private:
	void calc(void);

   private:
	glm::mat4 _model = glm::mat4(1.0f);
	glm::mat4 _view = glm::mat4(1.0f);
	glm::mat4 _proj = glm::mat4(1.0f);
	glm::mat4 _mvp = glm::mat4(1.0f);
};
}  // namespace GEngine

#endif