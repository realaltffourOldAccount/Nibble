/**
 * @file Shaders.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of a shader.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef SHADERS_H
#define SHADERS_H
#pragma once

// Shader's standard for uniform attributes
#define SHADER_ATTRIB_POS 0
#define SHADER_ATTRIB_COLOR 1
#define SHADER_ATTRIB_TEXCOORD 2  // if needed

#include <engine/files/FileManager.h>
#include "common.h"
#include "error_macros.h"

namespace GEngine {
/**
 * @brief An abstract definition of an OpenGL Program.
 *
 */
class Shader {
   public:
	/**
	 * @brief Construct a new Shader object.
	 *
	 * @param vsfile The path to the vertex shader file.
	 * @param fsfile The path to the fragment shader file.
	 */
	Shader(const std::string vsfile, const std::string fsfile);
	/**
	 * @brief Destroy the Shader object
	 *
	 */
	~Shader(void);

	/**
	 * @brief Binds the shader to be used.
	 *
	 */
	void bind(void);
	/**
	 * @brief Unbinds the shader.
	 *
	 */
	void unbind(void);

	/**
	 * @brief Destroy the Shader object manually.
	 *
	 */
	void destroy(void);

	/**
	 * @brief Get the Program Id.
	 *
	 * @return int
	 */
	int getProgId(void);

   private:
	GLuint _prog_id;
};
}  // namespace GEngine

#endif