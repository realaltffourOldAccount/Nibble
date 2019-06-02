/**
 * @file MVP.h
 * @author Ayham Mamoun (ayhamaboulafadl@gmail.com)
 * @brief Contains an abstract definition of a MVP matrix.
 * @version 0.1
 * @date 2019-05-31
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef MVP_H
#define MVP_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
/**
 * @brief An Abstract definition of an MVP matrix.
 *
 */
class MVP {
   public:
	/**
	 * @brief Construct a new MVP object.
	 *
	 * @param model	The model matrix.
	 * @param view		The view matrix.
	 * @param proj		The projection matrix.
	 */
	MVP(glm::mat4 model = glm::mat4(1.0f), glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 proj = glm::mat4(1.0f));
	/**
	 * @brief Destroy the MVP object.
	 *
	 */
	~MVP(void);

	/**
	 * @brief Binds the MVP matrix to be used.
	 * This assumes that the shader program is binded, beforehand.
	 *
	 * @param program
	 */
	void bind(GLuint program);

	/**
	 * @brief Updates the model matrix.
	 *
	 * @param model
	 */
	void updateModel(const glm::mat4 model);
	/**
	 * @brief Updates the view matrix.
	 *
	 * @param view
	 */
	void updateView(const glm::mat4 view);
	/**
	 * @brief Updates the projection matrix.
	 *
	 * @param proj
	 */
	void updateProj(const glm::mat4 proj);

	/**
	 * @brief Get the Model object.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getModel(void) const;
	/**
	 * @brief Get the View object.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getView(void) const;
	/**
	 * @brief Get the Proj object.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getProj(void) const;

	/**
	 * @brief Returns the MVP matrix.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 getMVP(void);

	/**
	 * @brief Destroys the MVP object manually.
	 *
	 */
	void destroy(void);

   private:
	/**
	 * @brief Calculates the MVP matrix.
	 *
	 */
	void calc(void);

   private:
	glm::mat4 _model = glm::mat4(1.0f);
	glm::mat4 _view = glm::mat4(1.0f);
	glm::mat4 _proj = glm::mat4(1.0f);
	glm::mat4 _mvp = glm::mat4(1.0f);
};
}  // namespace GEngine

#endif