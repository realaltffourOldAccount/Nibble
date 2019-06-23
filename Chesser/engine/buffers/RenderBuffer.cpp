#include "RenderBuffer.h"

namespace GEngine {
RenderBuffer::RenderBuffer(int w, int h, bool depth, bool stencil) {
	if (g_opengl_ver_major >= 3) {
		this->mWidth = w;
		this->mHeight = h;
		this->mDepthTests = depth;
		this->mStencilTests = stencil;

		GLCall(glGenRenderbuffers(1, &this->mRBO));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO));
		if (this->mDepthTests && this->mStencilTests) {
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
										 this->mWidth, this->mHeight));
		} else if (this->mDepthTests) {
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
										 this->mWidth, this->mHeight));
		} else if (this->mStencilTests) {
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8,
										 this->mWidth, this->mHeight));
		}
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	}
}
RenderBuffer::~RenderBuffer(void) { this->destroy(); }

void RenderBuffer::bind(void) {
	if (g_opengl_ver_major >= 3) {
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO));
	}
}
void RenderBuffer::unbind(void) {
	if (g_opengl_ver_major >= 3) {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}
void RenderBuffer::destroy(void) {
	if (g_opengl_ver_major >= 3) {
		glDeleteRenderbuffers(1, &this->mRBO);
	}
}

void RenderBuffer::clear(void) {
	if (g_opengl_ver_major >= 3) {
		this->bind();
		if (this->mDepthTests)
			glClear(GL_DEPTH_BUFFER_BIT);
		else if (this->mStencilTests)
			glClear(GL_STENCIL_BUFFER_BIT);
		this->unbind();
	}
}

void RenderBuffer::resize(int w, int h) {
	if (g_opengl_ver_major >= 3) {
		this->mWidth = w;
		this->mHeight = h;

		glGenRenderbuffers(1, &this->mRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO);
		if (this->mDepthTests && this->mStencilTests) {
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8,
								  this->mWidth, this->mHeight);
		} else if (this->mDepthTests) {
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH, this->mWidth,
								  this->mHeight);
		} else if (this->mStencilTests) {
			glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL, this->mWidth,
								  this->mHeight);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

}  // namespace GEngine