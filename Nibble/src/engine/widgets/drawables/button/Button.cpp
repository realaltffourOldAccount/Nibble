#include "Button.h"

namespace GEngine {
    namespace Widgets {
        namespace Drawables {
            Button::Button(GEngine::MVP* mvp, Rect shape, std::string text, std::string fontname, int wPx, int hPx, Colors::Color fill_color, int border, Colors::Color border_color) {
                this->mMVP = mvp;
                this->mRect = shape;
                this->mText = text;
                this->mFontName = fontname;
                this->mFillColor = fill_color;
                this->mBorderColor = border_color;
                this->mBorderSize = border;
                this->mTextWPx = wPx;
                this->mTextHPx = hPx;

                this->initShaders();
                this->initBuffers();
                this->initTextRenderer();
            }
            Button::Button(GEngine::MVP* mvp, Rect shape, std::string text, std::string fontname, int wPx, int hPx, std::string background_img, int border, Colors::Color border_color) {
                this->mMVP = mvp;
                this->mRect = shape;
                this->mText = text;
                this->mFontName = fontname;
                this->mBorderColor = border_color;
                this->mBorderSize = border;
                this->mTextWPx = wPx;
                this->mTextHPx = hPx;

                this->mTexture = new GEngine::Texture(background_img);

                this->initShaders();
                this->initBuffers();
                this->initTextRenderer();
            }
            Button::Button(void) {
                this->initShaders();
                this->initBuffers();
            }

            Button::~Button(void) {
                this->destroy();
            }

            void Button::initShaders(void) {
                if (db_shaders == nullptr)
                    db_shaders = LoadShader(g_config->_glsl_version, "dt", "vs/drawables/button.glsl", "fs/drawables/button.glsl");
            }

            void Button::initTextRenderer(void) {
              if (db_text == nullptr) 
                  db_text = new GEngine::Text::TextRenderer();
            }

            void Button::initBuffers(void) {
                this->mIndices = new GLubyte[6] {
                    0,1,2,3
                };

                this->mIBO = new GEngine::IBO(GL_STATIC_DRAW, sizeof(GLubyte) * 6, this->mIndices);
                // Place Holders
                GLfloat tr_x = this->mRect.x + this->mRect.w;
                GLfloat tr_y = this->mRect.y + this->mRect.h;
                GLfloat tl_x = this->mRect.x;
                GLfloat tl_y = this->mRect.y + this->mRect.h;

                GLfloat br_x = this->mRect.x + this->mRect.w;
                GLfloat br_y = this->mRect.y;
                GLfloat bl_x = this->mRect.x;
                GLfloat bl_y = this->mRect.y;

                GLfloat ttr_x = 1.0f;
                GLfloat ttr_y = 1.0f;
                GLfloat ttl_x = 0.0f;
                GLfloat ttl_y = 1.0f;

                GLfloat tbr_x = 1.0f;
                GLfloat tbr_y = 0.0f;
                GLfloat tbl_x = 0.0f;
                GLfloat tbl_y = 0.0f;

                this->mVertices = new GLfloat[32] {
                    tr_x, tr_y, ttr_x, ttr_y,
                        br_x, br_y, tbr_x, tbr_y,
                        bl_x, bl_y, tbl_x, tbl_y,
                        tl_x, tl_y, ttl_x, ttl_y
                };

                this->mVBO = new GEngine::VBO(GL_STATIC_DRAW, sizeof(GLfloat) * 32, this->mVertices);

                GEngine::ShaderAttrib* position_attrib;
                GEngine::ShaderAttrib* tex_cord_attrib;

                position_attrib = new GEngine::ShaderAttrib();
                position_attrib->_index = SHADER_ATTRIB_POS;
                position_attrib->_size = 2;
                position_attrib->_stride = 4 * sizeof(GLfloat);
                position_attrib->_type = GL_FLOAT;
                position_attrib->_isNorm = false;
                position_attrib->_isEnable = true;

                tex_cord_attrib = new GEngine::ShaderAttrib();
                tex_cord_attrib->_index = SHADER_ATTRIB_TEXCOORD;
                tex_cord_attrib->_size = 2;
                tex_cord_attrib->_stride = 4 * sizeof(GLfloat);
                tex_cord_attrib->_type = GL_FLOAT;
                tex_cord_attrib->_isNorm = false;
                tex_cord_attrib->_isEnable = true;

                vector<GEngine::ShaderAttrib*> attribs;
                attribs.push_back(position_attrib);
                attribs.push_back(tex_cord_attrib);

                this->mVAO = new GEngine::VAO(this->mVBO, attribs);
            }

            bool Button::eventHandler(Event* evt) {
                if (evt->IsInCategory(GEngine::EventCategory::EventCategoryMouse)) {
                    if (evt->GetEventType() == GEngine::EventType::MouseButtonPressed) {
                        GEngine::MouseButtonPressedEvent* event =
                            dynamic_cast<GEngine::MouseButtonPressedEvent*>(evt);

                        if (this->mRect.x <= static_cast<Input*>(g_input)->GetMouseX() <= this->mRect.x + this->mRect.w)
                            if (this->mRect.y <= static_cast<Input*>(g_input)->GetMouseY() <= this->mRect.y + this->mRect.h) {
                                if (static_cast<Input*>(g_input)->IsMouseKeyPressed(API_INPUT_MOUSE_BUTTON_LEFT)) this->mLeftClick(static_cast<Input*>(g_input)->GetMouseX(), static_cast<Input*>(g_input)->GetMouseY());
                                else if (static_cast<Input*>(g_input)->IsMouseKeyPressed(API_INPUT_MOUSE_BUTTON_RIGHT)) this->mLeftClick(static_cast<Input*>(g_input)->GetMouseX(), static_cast<Input*>(g_input)->GetMouseY());
                                return true;
                            }
                    }
                }
                return false;
            }

            void Button::render(void) {
                db_shaders->bind();
                this->mMVP->bind(db_shaders->getProgId());

                this->mVAO->bind();
                this->mIBO->bind();
                if (this->mTexture)
                    this->mTexture->bind();
                GLCall(glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, 0));
                if (this->mTexture)
                    this->mTexture->unbind();
                this->mVAO->unbind();
                this->mIBO->unbind();

                db_shaders->unbind();
            }
            void Button::tick(void) {}
            void Button::destroy(void) {}

            void Button::setText(std::string text) {}
            void Button::setFont(std::string name) {}
            void Button::setCurveRad(int rad) {}
            void Button::setBorderSize(int size) {}
            void Button::setFillColor(Colors::Color color) {}
            void Button::setBorderColor(Colors::Color color) {}

        }  // namespace Drawables
    }  // namespace Widgets
}  // namespace GEngine
