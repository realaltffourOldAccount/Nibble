#include "FrameBuffer.h"

namespace GEngine {
FrameBuffer::FrameBuffer(int w, int h, bool depth, bool stencil) {
	if (g_opengl_ver_major >= 3) {
		this->mWidth = w;
		this->mHeight = h;
		this->mDepthTests = depth;
		this->mStencilTests = stencil;

		// Generate Framebuffers
		GLCall(glGenFramebuffers(1, &mFBO));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->mFBO));

		// Generate color attachment.
		GLCall(glGenTextures(1, &this->mTex));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
							GL_UNSIGNED_BYTE, NULL));
		GLCall(
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
									  GL_TEXTURE_2D, this->mTex, 0));

		// Generate depths/stencil attachments.
		this->mRBO = new GEngine::RenderBuffer(w, h, depth, stencil);
		if (depth && stencil) {
			GLCall(glFramebufferRenderbuffer(
				GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
				this->mRBO->getRBO()));
		} else if (depth) {
			GLCall(glFramebufferRenderbuffer(
				GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
				this->mRBO->getRBO()));
		} else if (stencil) {
			GLCall(glFramebufferRenderbuffer(
				GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
				this->mRBO->getRBO()));
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
			GL_FRAMEBUFFER_COMPLETE) {
			Log::error(
				"Frame Buffer check failed.",
				Log::GenLogID(__LINE__, __FILE__, "FrameBuffer", __func__));
		}
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		GLfloat vertices[] = {// positions   // texCoords
							  -1.0f, 1.0f, 0.0f, 1.0f,  -1.0f, -1.0f,
							  0.0f,  0.0f, 1.0f, -1.0f, 1.0f,  0.0f,

							  -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  -1.0f,
							  1.0f,  0.0f, 1.0f, 1.0f,  1.0f,  1.0f};

		this->mVBO =
			new GEngine::VBO(GL_STATIC_DRAW, sizeof(vertices), &vertices);

		GEngine::ShaderAttrib *posattrib = new GEngine::ShaderAttrib(),
							  *texcordattrib = new GEngine::ShaderAttrib();
		posattrib->_index = 0;
		posattrib->_size = 2;
		posattrib->_stride = 4 * sizeof(GLfloat);
		posattrib->_offset = (void *)0;
		posattrib->_type = GL_FLOAT;
		posattrib->_isNorm = GL_FALSE;
		posattrib->_isEnable = true;

		texcordattrib->_index = 1;
		texcordattrib->_size = 2;
		texcordattrib->_stride = 4 * sizeof(GLfloat);
		texcordattrib->_offset = (void *)(2 * sizeof(GLfloat));
		texcordattrib->_type = GL_FLOAT;
		texcordattrib->_isNorm = GL_FALSE;
		texcordattrib->_isEnable = true;

		std::vector<GEngine::ShaderAttrib *> attribs;
		attribs.push_back(posattrib);
		attribs.push_back(texcordattrib);

		this->mVAO = new GEngine::VAO(this->mVBO, attribs);

		if (fbo_shader == nullptr) {
#if defined(__DESKTOP__)
			if (g_glsl_version >= 3.0) {
				fbo_shader = new GEngine::Shader("glsl/v3.x/dt/vs/fbo.glsl",
												 "glsl/v3.x/dt/fs/fbo.glsl");
			} else {
				fbo_shader = new GEngine::Shader("glsl/v1.x/dt/vs/fbo.glsl",
												 "glsl/v1.x/dt/fs/fbo.glsl");
			}
#elif defined(__WEB__)
			if (g_glsl_version >= 3.0) {
				fbo_shader = new GEngine::Shader("glsl/v3.x/em/vs/fbo.glsl",
												 "glsl/v3.x/em/fs/fbo.glsl");
			} else {
				fbo_shader = new GEngine::Shader("glsl/v1.x/em/vs/fbo.glsl",
												 "glsl/v1.x/em/fs/fbo.glsl");
			}
#elif defined(__ANDROID__)
			if (g_glsl_version >= 3.0) {
				fbo_shader = new GEngine::Shader("glsl/v3.x/es/vs/fbo.glsl",
												 "glsl/v3.x/es/fs/fbo.glsl");
			} else {
				fbo_shader = new GEngine::Shader("glsl/v1.x/es/vs/fbo.glsl",
												 "glsl/v1.x/es/fs/fbo.glsl");
			}
#endif
		}
	}
}
FrameBuffer::~FrameBuffer(void) { this->destroy(); }

void FrameBuffer::bind(void) {
	if (g_opengl_ver_major >= 3) {
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->mFBO));
	}
}
void FrameBuffer::unbind(void) {
	if (g_opengl_ver_major >= 3) {
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}
void FrameBuffer::destroy(void) {
	GLCall(glDeleteFramebuffers(1, &this->mFBO));
	delete mRBO;
}

void FrameBuffer::clear(void) {
	if (g_opengl_ver_major >= 3) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		if (this->mDepthTests) GLCall(glClear(GL_DEPTH_BUFFER_BIT));
		if (this->mStencilTests) GLCall(glClear(GL_STENCIL_BUFFER_BIT));
	}
}

void FrameBuffer::resize(int w, int h) {
	if (g_opengl_ver_major >= 3) {
		this->mWidth = w;
		this->mHeight = h;

		GLCall(glBindTexture(GL_TEXTURE_2D, mTex));
		GLCall(
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
							   GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
							   GL_CLAMP_TO_EDGE));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
							GL_UNSIGNED_BYTE, NULL));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}

void FrameBuffer::render(void) {
	if (g_opengl_ver_major >= 3) {
		this->unbind();
		fbo_shader->bind();

		this->mVAO->bind();
		this->mVBO->bind();
		// this->mIBO->bind();
		GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		// this->mIBO->unbind();
		fbo_shader->unbind();
		this->mVAO->unbind();
		this->mVBO->unbind();
	}
}

}  // namespace GEngine