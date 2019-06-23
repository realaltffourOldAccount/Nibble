/**
 * @file RenderBuffer.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of an OpenGL Render Buffer.
 * @version 0.1
 * @date 2019-06-13
 *
 */

#include "common.h"
#include "error_macros.h"

namespace GEngine {
/**
 * @brief An abstract definition of an OpenGL Render Buffer.
 *
 */
class RenderBuffer {
   public:
	/**
	 * @brief Construct a new Render Buffer object.
	 *
	 * @param w			The size of the Render Buffer Object.
	 * @param h			The size of the Render Buffer Object.
	 * @param depth		Enables depth test for the render buffer.
	 * @param stencil	Enables stencil test for the render buffer.
	 */
	RenderBuffer(int w, int h, bool depth, bool stencil);
	/**
	 * @brief Destroy the Render Buffer object.
	 *
	 */
	~RenderBuffer(void);

	/**
	 * @brief Binds the Render Buffer object to be used.
	 *
	 */
	void bind(void);
	/**
	 * @brief Unbinds the Render Buffer Object.
	 *
	 */
	void unbind(void);
	/**
	 * @brief Destroy the Render Buffer Object manually.
	 *
	 */
	void destroy(void);

	/**
	 * @brief Clears the Render Buffer Object.
	 *
	 */
	void clear(void);

	/**
	 * @brief Returns the RBO Handle.
	 *
	 * @return unsigned int The Handle.
	 */
	unsigned int getRBO(void) { return mRBO; }

	/**
	 * @brief Resizes the Render Buffer Object.
	 *
	 * @param w	The size of the Render Buffer Object.
	 * @param h	The size of the Render Buffer Object.
	 */
	void resize(int w, int h);

   private:
	unsigned int mRBO = -1;

	int mWidth = 0;
	int mHeight = 0;

	bool mDepthTests = false;
	bool mStencilTests = false;
};
}  // namespace GEngine