#include "BlurEffect.h"

namespace GEngine {
    namespace Effects {
        namespace Post {
            GEngine::Shader* ep_blur_shaders = nullptr;

            BlurEffect::BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination) :
                PostEffect(source, destination, PostEffectID::Blur) {
                    if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {

                        mKernel = {
                            1.0, 2.0, 1.00,
                            2.0, mStrength, 2.00,
                            1.0, 2.0, 1.0
                        };

                        int weighter = 0;
                        for (int i = 0; i < 3; i++) 
                            for (int j = 0; j < 3; j++)
                                weighter += mKernel[i][j];

                        for (int i = 0; i < 3; i++)
                            for (int j = 0; j < 3; j++)
                                mKernel[i][j] /= weighter;

                        initShaders();
                        initBuffers();
                    }
                }

            BlurEffect::BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int strength) :
                PostEffect(source, destination, PostEffectID::Blur) {
                    if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                        this->mSource = source;
                        this->mDestination = destination;
                        this->mStrength = strength;

                        int weighter = 0;
                        for (int i = 0; i < 3; i++) 
                            for (int j = 0; j < 3; j++)
                                weighter += mKernel[i][j];

                        for (int i = 0; i < 3; i++)
                            for (int j = 0; j < 3; j++)
                                mKernel[i][j] /= weighter;

                        initShaders();
                        initBuffers();
                    }
                }
            BlurEffect::~BlurEffect(void) { this->destroy(); }

            void BlurEffect::render(void) {
                if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                    this->mDestination->bind();
                    ep_blur_shaders->bind();

                    GLCall(glUniformMatrix3fv(glGetUniformLocation(ep_blur_shaders->getProgId(), "mKernel"), 1, GL_FALSE, &this->mKernel[0][0]));
                    this->mVAO->bind();
                    this->mVBO->bind();
                    GLCall(glBindTexture(GL_TEXTURE_2D, this->mSource->GetTexture()));
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
                    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
                    this->mVBO->unbind();
                    this->mVAO->unbind();
                    ep_blur_shaders->unbind();
                    this->mDestination->unbind();

                    auto holder = this->mSource;
                    this->mSource = this->mDestination;
                    this->mDestination = holder;
                }
            }
            void BlurEffect::tick(void) {}
            void BlurEffect::destroy(void) {
                this->mVAO->destroy();
                this->mVBO->destroy();
                this->mIBO->destroy();
            }

            void BlurEffect::initShaders(void) {
                if (!ep_blur_shaders) {
                    ep_blur_shaders =
                        LoadShader(g_config->_glsl_version, "dt", "vs/effects/post/blur.glsl", "fs/effects/post/blur.glsl");
                }
            }

            void BlurEffect::initBuffers(void) {
                if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                    this->mBufferData = new GLfloat[32]{ 
                        // positions   // texCoords
                        -1.0f,  1.0f,  0.0f, 1.0f,
                            -1.0f, -1.0f,  0.0f, 0.0f,
                            1.0f, -1.0f,  1.0f, 0.0f,

                            -1.0f,  1.0f,  0.0f, 1.0f,
                            1.0f, -1.0f,  1.0f, 0.0f,
                            1.0f,  1.0f,  1.0f, 1.0f
                    };                    
                    this->mVBO = new GEngine::VBO(GL_STATIC_DRAW, sizeof(GLfloat) * 32, this->mBufferData);

                    GEngine::ShaderAttrib* position_attrib;
                    GEngine::ShaderAttrib* tex_cord_attrib;

                    position_attrib = new GEngine::ShaderAttrib();
                    if (g_config->_openglvMajor >= 3)
                        position_attrib->_index = SHADER_ATTRIB_POS;
                    else
                        position_attrib->_index =
                            glGetAttribLocation(ep_blur_shaders->getProgId(), "aPos");

                    position_attrib->_size = 2;
                    position_attrib->_stride = 4 * sizeof(GLfloat);
                    position_attrib->_offset = (void*)0;
                    position_attrib->_type = GL_FLOAT;
                    position_attrib->_isNorm = false;
                    position_attrib->_isEnable = true;

                    tex_cord_attrib = new GEngine::ShaderAttrib();

                    if (g_config->_openglvMajor >= 3)
                        tex_cord_attrib->_index = SHADER_ATTRIB_TEXCOORD;
                    else
                        tex_cord_attrib->_index =
                            glGetAttribLocation(ep_blur_shaders->getProgId(), "aTexCoord");

                    tex_cord_attrib->_size = 2;
                    tex_cord_attrib->_stride = 4 * sizeof(GLfloat);
                    tex_cord_attrib->_offset = (void*)(2 * sizeof(GLfloat));
                    tex_cord_attrib->_type = GL_FLOAT;
                    tex_cord_attrib->_isNorm = false;
                    tex_cord_attrib->_isEnable = true;

                    this->mShaderAttribs.push_back(position_attrib);
                    this->mShaderAttribs.push_back(tex_cord_attrib);

                    this->mVAO = new GEngine::VAO(this->mVBO, this->mShaderAttribs);
                }
            }

        }  // namespace Post
    }  // namespace Effects
}  // namespace GEngine
