/**
 * @file VAO.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains an abstract definition of an OpenGL Vertex Array Buffer.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef VAO_H
#define VAO_H
#pragma once

#include "BufferObject.h"
#include "VBO.h"
#include "common.h"
#include "error_macros.h"

namespace GEngine {
/**
 * @brief Represents a shader attribute.
 *
 */
struct ShaderAttrib {
	GLint _index;
	GLsizei _size;
	GLsizei _stride;
	void* _offset;
	GLenum _type;
	GLboolean _isNorm = false;
	GLboolean _isEnable = true;
};

/**
 * @brief An abstract definition of an OpenGL Vertex Array Buffer.
 *
 */
class VAO {
   public:
	/**
	 * @brief Construct a new VAO object.
	 *
	 * @param vbo		The Vertex Buffer to be bound to.
	 * @param attribs	The attributes to be applied.
	 */
	VAO(GEngine::VBO* vbo, std::vector<ShaderAttrib*> attribs);
	/**
	 * @brief Construct a new VAO object.
	 *
	 * @param attribs	The attributes to be applied.
	 */
	VAO(vector<ShaderAttrib*> attribs);
	/**
	 * @brief Destroy the VAO object.
	 *
	 */
	~VAO(void);

	/**
	 * @brief Binds the Vertex Array Buffer Instance to be used.
	 *
	 */
	void bind(void);
	/**
	 * @brief Unbinds the Vertex Array Buffer Instance.
	 *
	 */
	void unbind(void);

	/**
	 * @brief Destroy the Vertex Array Buffer Instance manually.
	 *
	 */
	void destroy(void);

   private:
	/**
	 * @brief Enables an individual shader attribute.
	 *
	 * @param attrib The attribute to be enabled.
	 */
	void enableAttrib(ShaderAttrib* attrib);

	GEngine::VBO* _vbo = nullptr;
	GLuint _vaoID;
	vector<ShaderAttrib*> _attribs;
};
}  // namespace GEngine

#endif