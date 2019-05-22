#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include "common.h"

#include "engine/Point.h"
#include "engine/Rect.h"

#include "engine/buffers/buffers.h"
#include "engine/shaders/Shaders.h"
#include "engine/textures/Texture.h"

namespace GEngine {
class Object {
   public:
	Object(std::string tex_file, Rect shape, Rect texcord = Rect(0, 0, 1, 1),
		   GEngine::Texture* tex = nullptr);
	~Object(void);

	void bind() const;
	void unbind() const;

	glm::mat4 getModel(void) const;

	void translate(glm::vec2 vec);
	void scale(glm::vec2 vec);

	GEngine::Texture* getTex(void) const;

	void destroy(void);

   private:
	GEngine::Texture* _tex = nullptr;
	GEngine::VBO* _vbo = nullptr;
	GEngine::IBO* _ibo = nullptr;
	GEngine::VAO* _vao = nullptr;

	Rect _shape;

	GLfloat* _buffer_data = nullptr;
	GLuint* _indices_data = nullptr;

	vector<GEngine::ShaderAttrib*> _shader_attribs;

	glm::mat4 model = glm::mat4(1.0f);
};
}  // namespace GEngine

#endif