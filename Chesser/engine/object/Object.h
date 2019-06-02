/**
 * @file Object.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains a basic definition of an Object.
 * @version 0.1
 * @date 2019-05-31
 *
 */
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
/**
 * @brief A definition of a Renderable Object.
 *
 */
class Object {
   public:
	/**
	 * @brief Construct a new Object object.
	 *
	 * @param tex_file	The file to load the texture file.
	 * @param shape		The shape of the object.
	 * @param texcord	The texture cordinates.
	 * @param tex		The texture to be used.
	 */
	Object(std::string tex_file, Rect shape, Rect texcord = Rect(0, 0, 1, 1),
		   GEngine::Texture* tex = nullptr);
	/**
	 * @brief Destroy the Object object
	 *
	 */
	~Object(void);

	/**
	 * @brief Binds the Object to be used.
	 *
	 */
	void bind() const;
	/**
	 * @brief Unbinds the Object.
	 *
	 */
	void unbind() const;

	/**
	 * @brief Get the Model object.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getModel(void) const;

	/**
	 * @brief Translates the MVP matrix.
	 *
	 * @param vec
	 */
	void translate(glm::vec2 vec);
	/**
	 * @brief Scales the MVP matrix.
	 *
	 * @param vec
	 */
	void scale(glm::vec2 vec);

	/**
	 * @brief Get the Texture object.
	 *
	 * @return GEngine::Texture*
	 */
	GEngine::Texture* getTex(void) const;

	/**
	 * @brief Destory the Object object manually.
	 *
	 */
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