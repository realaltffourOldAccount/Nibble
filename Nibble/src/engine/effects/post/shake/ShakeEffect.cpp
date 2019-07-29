#include "ShakeEffect.h"

namespace GEngine {
    namespace Effects {
        namespace Post { 
            GEngine::Shader* ep_shake_shaders = nullptr;
            ShakeEffect::ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination) : PostEffect(source, destination, PostEffectID::Shake){
                if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                    this->mSource = source;
                    this->mDestination = destination;
                    this->initShaders();
                    this->initBuffers();
                }
            }

            ShakeEffect::ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int ticks, float strength)  : PostEffect(source, destination, PostEffectID::Shake){
                if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                    this->mSource = source;
                    this->mDestination = destination;
                    this->mTicks = ticks;
                    this->mStrength = strength;
                    this->initShaders();
                    this->initBuffers();
                }
            }

            ShakeEffect::~ShakeEffect(void) { this->destroy(); }

            void ShakeEffect::render(void) {
                if (g_config->_coreframeBufferSupport || g_config->_ARBframeBufferSupport || g_config->_EXTframeBufferSupport) {
                    if (this->mCurrentTick <= this->mTicks){
                        this->mDestination->bind();
                        ep_shake_shaders->bind();

                        GLCall(glUniform1i(glGetUniformLocation(ep_shake_shaders->getProgId(), "time"), this->mCurrentTick));
                        GLCall(glUniform1f(glGetUniformLocation(ep_shake_shaders->getProgId(), "strength"), this->mStrength));
                        this->mVAO->bind();
                        this->mVBO->bind();
                        GLCall(glBindTexture(GL_TEXTURE_2D, this->mSource->GetTexture()));
                        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
                        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
                        this->mVBO->unbind();
                        this->mVAO->unbind();
                        ep_shake_shaders->unbind();
                        this->mDestination->unbind();

                        auto holder = this->mSource;
                        this->mSource = this->mDestination;
                        this->mDestination = holder;
                    }
                }
            }
            void ShakeEffect::tick(void) {
                this->mCurrentTick++;
            }
            void ShakeEffect::destroy(void) {
                this->mVAO->destroy();
                this->mVBO->destroy();
                this->mIBO->destroy();
            }

            void ShakeEffect::initShaders(void) {
                if (!ep_shake_shaders) {
                    ep_shake_shaders = LoadShader(g_config->_glsl_version, "dt", "vs/effects/post/shake.glsl", "fs/effects/post/shake.glsl");
                }
            }
            void ShakeEffect::initBuffers(void) {
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
                            glGetAttribLocation(ep_shake_shaders->getProgId(), "aPos");

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
                            glGetAttribLocation(ep_shake_shaders->getProgId(), "aTexCoord");

                    tex_cord_attrib->_size = 2;
                    tex_cord_attrib->_stride = 4 * sizeof(GLfloat);
                    tex_cord_attrib->_offset = (void*)(2 * sizeof(GLfloat));
                    tex_cord_attrib->_type = GL_FLOAT;
                    tex_cord_attrib->_isNorm = false;
                    tex_cord_attrib->_isEnable = true;

                    this->mShaderAttribs.push_back(position_attrib);
                    this->mShaderAttribs.push_back(tex_cord_attrib);

                    this->mVAO = new GEngine::VAO(this->mVBO, this->mShaderAttribs);}
            }
        }
    }
}
