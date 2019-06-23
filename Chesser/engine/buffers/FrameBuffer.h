/**
 * @file FrameBuffer.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of an OpenGL Frame Buffer.
 * @version 0.1
 * @date 2019-06-13
 *
 */

#include <engine/shaders/Shaders.h>
#include <engine/textures/Texture.h>

#include "IBO.h"
#include "RenderBuffer.h"
#include "VAO.h"
#include "VBO.h"

namespace GEngine {
static GEngine::Shader* fbo_shader = nullptr;
/**
 * @brief An abstract definition of an OpenGL Frame Buffer.
 *
 */
class FrameBuffer {
   public:
	/**
	 * @brief Construct a new Frame Buffer object.
	 *
	 * @param w 				The size of the buffer.
	 * @param h					The size of the buffer.
	 * @param depthTests		Enables depth tests.
	 * @param stencilTests		Enables stencil tests.
	 */
	FrameBuffer(int w, int h, bool depthTests, bool stencilTests);
	/**
	 * @brief Destroy the Frame Buffer object.
	 *
	 */
	~FrameBuffer(void);

	/**
	 * @brief Binds the Frame Buffer object to be used.
	 *
	 */
	void bind(void);
	/**
	 * @brief Unbinds the Frame Buffer object.
	 *
	 */
	void unbind(void);
	/**
	 * @brief Destroy the Frame Buffer object manually.
	 *
	 */
	void destroy(void);

	/**
	 * @brief Clears the Frame Buffer object.
	 *
	 */
	void clear(void);

	/**
	 * @brief Resizes the Frame Buffer object.
	 *
	 * @param w	The size of the Frame Buffer object.
	 * @param h	The size of the Frame Buffer object.
	 */
	void resize(int w, int h);

	void render(void);

   private:
	unsigned int mFBO = -1;
	unsigned int mTex = -1;
	GEngine::RenderBuffer* mRBO = nullptr;
	GEngine::VBO* mVBO = nullptr;
	GEngine::VAO* mVAO = nullptr;
	GEngine::IBO* mIBO = nullptr;

	bool mDepthTests = false;
	bool mStencilTests = false;
	int mWidth = 0;
	int mHeight = 0;

	glm::mat4 mMVP = glm::mat4(1.0f);
};
}  // namespace GEngine