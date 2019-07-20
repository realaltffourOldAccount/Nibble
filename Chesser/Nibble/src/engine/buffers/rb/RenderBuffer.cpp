#include "RenderBuffer.h"

namespace GEngine {
    RenderBuffer::RenderBuffer(int w, int h, bool depth, bool stencil) {
        this->mWidth = w;
        this->mHeight = h;
        this->mDepthTests = depth;
        this->mStencilTests = stencil;

        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            GLCall(glGenRenderbuffers(1, &this->mRBO));
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO));
            if (this->mDepthTests && this->mStencilTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->mWidth, this->mHeight));
            } else if (this->mDepthTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, this->mWidth, this->mHeight));
            } else if (this->mStencilTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, this->mWidth, this->mHeight));
            }
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
        }
        else if (g_config->_EXTrenderBufferSupport) {
            GLCall(glGenRenderbuffersEXT(1, &this->mRBO));
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, this->mRBO));
            if (this->mDepthTests || this->mStencilTests) {
                GLCall(glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, this->mWidth, this->mHeight));
            }
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0));
        }
    }
    RenderBuffer::~RenderBuffer(void) { this->destroy(); }

    void RenderBuffer::bind(void) {
        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO));
        }
        else if (g_config->_EXTrenderBufferSupport) {
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, this->mRBO));
        }
    }
    void RenderBuffer::unbind(void) {
        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
        }
        else if (g_config->_EXTrenderBufferSupport) {
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0));
        }
    }
    void RenderBuffer::destroy(void) {
        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            GLCall(glDeleteRenderbuffers(1, &this->mRBO));
        }
        else if (g_config->_EXTrenderBufferSupport) {
            GLCall(glDeleteRenderbuffersEXT(1, &this->mRBO));
        }
    }

    void RenderBuffer::clear(void) {
        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            this->bind();
            if (this->mDepthTests)
                glClear(GL_DEPTH_BUFFER_BIT);
            else if (this->mStencilTests)
                glClear(GL_STENCIL_BUFFER_BIT);
            this->unbind();
        }
        else if (g_config->_EXTrenderBufferSupport) {
            this->bind();
            if (this->mDepthTests)
                glClear(GL_DEPTH_BUFFER_BIT);
            else if (this->mStencilTests)
                glClear(GL_STENCIL_BUFFER_BIT);
            this->unbind();
        }
    }

    void RenderBuffer::resize(int w, int h) {
        this->mWidth = w;
        this->mHeight = h;

        if (g_config->_corerenderBufferSupport || g_config->_ARBrenderBufferSupport) {
            GLCall(glGenRenderbuffers(1, &this->mRBO));
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->mRBO));
            if (this->mDepthTests && this->mStencilTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, this->mWidth, this->mHeight));
            } else if (this->mDepthTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, this->mWidth, this->mHeight));
            } else if (this->mStencilTests) {
                GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, this->mWidth, this->mHeight));
            }
            GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
        }
        else if (g_config->_EXTrenderBufferSupport) {
            GLCall(glGenRenderbuffersEXT(1, &this->mRBO));
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, this->mRBO));
            if (this->mDepthTests || this->mStencilTests) {
                GLCall(glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, this->mWidth, this->mHeight));
            }
            GLCall(glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0));
        }
    }

}  // namespace GEngine
