#include "FrameBuffer.h"

namespace GEngine {
    FrameBuffer::FrameBuffer(int w, int h, bool depth, bool stencil) {
        this->mWidth = w;
        this->mHeight = h;
        this->mDepthTests = depth;
        this->mStencilTests = stencil;

        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            // Generate Framebuffers
            GLCall(glGenFramebuffers(1, &mFBO));
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->mFBO));

            // Generate color attachment.
            GLCall(glGenTextures(1, &this->mTex));
            GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
                        GL_UNSIGNED_BYTE, NULL));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
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
        }
        else if (g_config->_EXTframeBufferSupport) {
            // Generate Framebuffers.
            GLCall(glGenFramebuffersEXT(1, &mFBO));
            GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, this->mFBO));

            // Generate color attachment.
            GLCall(glGenTextures(1, &this->mTex));
            GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
            GLCall(glGenerateMipmapEXT(GL_TEXTURE_2D));
            GLCall(
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); GLCall(
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GLCall(glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                        GL_TEXTURE_2D, this->mTex, 0));

            // Generate depths/stencil attachments.
            this->mRBO = new GEngine::RenderBuffer(w, h, depth, stencil);
            if (depth && stencil) {
                GLCall(glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->mRBO->getRBO()));
                GLCall(glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, this->mRBO->getRBO()));
            }
            else if (depth) {
                GLCall(glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->mRBO->getRBO()));
            }
            else if (stencil) {
                GLCall(glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, this->mRBO->getRBO()));
            }

            // Check framebuffer completion.
            if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT) {
                Log::error("Frame Buffer Check failed.", Log::GenLogID(__LINE__, __FILE__, "FrameBuffer", __func__));
            }
            GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
        }

        if (fbo_shader == nullptr) {
            fbo_shader = LoadShader(g_config->_glsl_version, "dt", "vs/fbo.glsl", "fs/fbo.glsl");
        }

        GLfloat vertices[] = { 
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
        };
        this->mVBO = new GEngine::VBO(GL_STATIC_DRAW, sizeof(vertices), &vertices);

        fbo_shader->bind();
        GEngine::ShaderAttrib *posattrib = new GEngine::ShaderAttrib(),
            *texcordattrib = new GEngine::ShaderAttrib();
        if (g_config->_openglvMajor >= 3)
            posattrib->_index = SHADER_ATTRIB_POS;
        else posattrib->_index = glGetAttribLocation(fbo_shader->getProgId(), "aPos");
        posattrib->_size = 2;
        posattrib->_stride = 4 * sizeof(GLfloat);
        posattrib->_offset = (void *)0;
        posattrib->_type = GL_FLOAT;
        posattrib->_isNorm = false;
        posattrib->_isEnable = true;

        if (g_config->_openglvMajor >= 3)
            texcordattrib->_index = SHADER_ATTRIB_TEXCOORD;
        else texcordattrib->_index = glGetAttribLocation(fbo_shader->getProgId(), "aTexCoords");
        texcordattrib->_size = 2;
        texcordattrib->_stride = 4 * sizeof(GLfloat);
        texcordattrib->_offset = (void *)(2 * sizeof(GLfloat));
        texcordattrib->_type = GL_FLOAT;
        texcordattrib->_isNorm = false;
        texcordattrib->_isEnable = true;

        std::vector<GEngine::ShaderAttrib *> attribs;
        attribs.push_back(posattrib);
        attribs.push_back(texcordattrib);

        this->mVAO = new GEngine::VAO(this->mVBO, attribs);
        fbo_shader->unbind();
    }
    FrameBuffer::~FrameBuffer(void) { this->destroy(); }

    void FrameBuffer::bind(void) {
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->mFBO));
        }
        else if (g_config->_EXTframeBufferSupport) {
            GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, this->mFBO));
        }
    }
    void FrameBuffer::unbind(void) {
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }
        else if (g_config->_EXTframeBufferSupport) {
            GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
        }
    }
    void FrameBuffer::destroy(void) {
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            GLCall(glDeleteFramebuffers(1, &this->mFBO));
            delete mRBO;
        }
        else if (g_config->_EXTframeBufferSupport) {
            GLCall(glDeleteFramebuffersEXT(1, &this->mFBO));
        }
    }

    void FrameBuffer::clear(void) {
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            if (this->mDepthTests) GLCall(glClear(GL_DEPTH_BUFFER_BIT));
            if (this->mStencilTests) GLCall(glClear(GL_STENCIL_BUFFER_BIT));
        }
        else if (g_config->_EXTframeBufferSupport) {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            if (this->mDepthTests) GLCall(glClear(GL_DEPTH_BUFFER_BIT));
            if (this->mStencilTests) GLCall(glClear(GL_STENCIL_BUFFER_BIT));           
        }
    }

    void FrameBuffer::resize(int w, int h) {
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
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
        else if (g_config->_EXTframeBufferSupport) {
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
        if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport) {
            this->unbind();
            fbo_shader->bind();

            this->mVAO->bind();
            this->mVBO->bind();
            GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
            fbo_shader->unbind();
            this->mVAO->unbind();
            this->mVBO->unbind();
        }
        else if (g_config->_EXTframeBufferSupport) {
            this->unbind();
            fbo_shader->bind();

            this->mVAO->bind();
            this->mVBO->bind();
            GLCall(glBindTexture(GL_TEXTURE_2D, this->mTex));
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
            fbo_shader->unbind();
            this->mVAO->unbind();
            this->mVBO->unbind();           
        }
    }

}  // namespace GEngine
