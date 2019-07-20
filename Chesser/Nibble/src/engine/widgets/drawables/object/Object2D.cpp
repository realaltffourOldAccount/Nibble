#include "Object2D.h"

namespace GEngine {
    namespace Widgets {
        namespace Drawables {
            GEngine::Shader* do_shaders = nullptr;

            Object2D::Object2D(Rect shape, GEngine::MVP* mvp) {
                this->mShape = shape;
                this->mMVP = mvp;
                this->init();
            }
            Object2D::Object2D(Rect shape, GEngine::MVP* mvp, std::string tex_file) {
                this->mShape = shape;
                this->mMVP = mvp;
                this->mTexFile = tex_file;
                this->mTexCord = GEngine::Rect(0, 0, 1, 1);
                this->init();
                this->initDefaultObject();
            }
            Object2D::Object2D(Rect shape, GEngine::MVP* mvp, GEngine::Texture* tex,
                    Rect texcord) {
                this->mShape = shape;
                this->mMVP = mvp;
                this->mTex = tex;
                this->mTexCord = texcord;
                this->init();
            }

            Object2D::~Object2D(void) { this->destroy(); }

            void Object2D::init() { this->initShaders(); }

            void Object2D::initShaders() {
#if defined(__DESKTOP__)
                do_shaders =
                    LoadShader(g_config->_glsl_version, "dt", "vs/smple.glsl", "fs/smple.glsl");
#elif defined(__WEB__)
                do_shaders =
                    LoadShader(g_config->_glsl_version, "em", "vs/smple.glsl", "fs/smple.glsl");
#elif defined(__ANDROID__)
                do_shaders =
                    LoadShader(g_cofig->_glsl_version, "es", "vs/smple.glsl", "fs/smple.glsl");
#endif
            }

            void Object2D::initDefaultObject() {
                this->mTex = new GEngine::Texture(this->mTexFile);

                this->mIndicesData = new GLubyte[6]{
                    0, 1, 3,  // first triangle
                        1, 2, 3,  // second triangle
                };

                // Create indices buffer
                this->mIBO =
                    new GEngine::IBO(GL_STATIC_DRAW, sizeof(GLubyte) * 6, this->mIndicesData);

                // Place holders for the buffer object.
                GLfloat tr_x = this->mShape.x + this->mShape.w;
                GLfloat tr_y = this->mShape.y + this->mShape.h;
                GLfloat tl_x = this->mShape.x;
                GLfloat tl_y = this->mShape.y + this->mShape.h;

                GLfloat br_x = this->mShape.x + this->mShape.w;
                GLfloat br_y = this->mShape.y;
                GLfloat bl_x = this->mShape.x;
                GLfloat bl_y = this->mShape.y;

                GLfloat ttr_x = this->mTexCord.x + this->mTexCord.w;
                GLfloat ttr_y = this->mTexCord.y + this->mTexCord.h;
                GLfloat ttl_x = this->mTexCord.x;
                GLfloat ttl_y = this->mTexCord.y + this->mTexCord.h;

                GLfloat tbr_x = this->mTexCord.x + this->mTexCord.w;
                GLfloat tbr_y = this->mTexCord.y;
                GLfloat tbl_x = this->mTexCord.x;
                GLfloat tbl_y = this->mTexCord.y;

                // Set the buffer data.
                this->mBufferData = new GLfloat[32]{
                    // positions        // colors           // texture cords
                    tr_x, tr_y, 0.0f, 1.0f, 1.0f, 1.0f, ttr_x, ttr_y,  // top right
                        br_x, br_y, 0.0f, 1.0f, 1.0f, 1.0f, tbr_x, tbr_y,  // bottom right
                        bl_x, bl_y, 0.0f, 1.0f, 1.0f, 1.0f, tbl_x, tbl_y,  // bottom left
                        tl_x, tl_y, 0.0f, 1.0f, 1.0f, 1.0f, ttl_x, ttl_y,  // top left
                };

                this->mVBO =
                    new GEngine::VBO(GL_STATIC_DRAW, sizeof(GLfloat) * 32, this->mBufferData);

                // Set up the vertex attributes: pos, color, tcords, etc.
                GEngine::ShaderAttrib* position_attrib;
                GEngine::ShaderAttrib* color_attrib;
                GEngine::ShaderAttrib* tex_cord_attrib;

                position_attrib = new GEngine::ShaderAttrib();
                if (g_config->_openglvMajor >= 3)
                    position_attrib->_index = SHADER_ATTRIB_POS;
                else
                    position_attrib->_index =
                        glGetAttribLocation(do_shaders->getProgId(), "aPos");
                position_attrib->_size = 3;
                position_attrib->_stride = 8 * sizeof(GLfloat);
                position_attrib->_offset = (void*)0;
                position_attrib->_type = GL_FLOAT;
                position_attrib->_isNorm = false;
                position_attrib->_isEnable = true;

                color_attrib = new GEngine::ShaderAttrib();
                if (g_config->_openglvMajor >= 3)
                    color_attrib->_index = SHADER_ATTRIB_COLOR;
                else
                    color_attrib->_index =
                        glGetAttribLocation(do_shaders->getProgId(), "aColor");
                color_attrib->_size = 3;
                color_attrib->_stride = 8 * sizeof(GLfloat);
                color_attrib->_offset = (void*)(3 * sizeof(GLfloat));
                color_attrib->_type = GL_FLOAT;
                color_attrib->_isNorm = false;
                color_attrib->_isEnable = true;

                tex_cord_attrib = new GEngine::ShaderAttrib();
                if (g_config->_openglvMajor >= 3)
                    tex_cord_attrib->_index = SHADER_ATTRIB_TEXCOORD;
                else
                    tex_cord_attrib->_index =
                        glGetAttribLocation(do_shaders->getProgId(), "aTexCoord");
                tex_cord_attrib->_size = 2;
                tex_cord_attrib->_stride = 8 * sizeof(GLfloat);
                tex_cord_attrib->_offset = (void*)(6 * sizeof(GLfloat));
                tex_cord_attrib->_type = GL_FLOAT;
                tex_cord_attrib->_isNorm = false;
                tex_cord_attrib->_isEnable = true;

                this->mShaderAttribs.push_back(position_attrib);
                this->mShaderAttribs.push_back(color_attrib);
                this->mShaderAttribs.push_back(tex_cord_attrib);

                this->mVAO = new GEngine::VAO(this->mVBO, this->mShaderAttribs);
            }

            void Object2D::render(void) {
                do_shaders->bind();
                this->mMVP->updateModel(this->mModel);
                this->mMVP->bind(do_shaders->getProgId());
                this->mTex->bind();
                this->mVAO->bind();
                this->mVBO->bind();
                this->mIBO->bind();
                GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0));
                this->mTex->unbind();
                this->mVAO->unbind();
                this->mVBO->unbind();
                this->mIBO->unbind();
                do_shaders->unbind();
            }
            void Object2D::tick(void) {}
            void Object2D::destroy(void) {
                this->mTex->destroy();
                this->mVAO->destroy();
                this->mVBO->destroy();
                this->mIBO->destroy();
            }

            bool Object2D::eventHandler(Event* evt) { return true; }

        }  // namespace Drawables
    }  // namespace Widgets
}  // namespace GEngine
