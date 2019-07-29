/**
 * @file Button.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains the definition of a button.
 * @version 0.1
 * @date 2019-06-10
 *
 */

#include <engine/Rect.h>
#include <engine/buffers/buffers.h>
#include <engine/shaders/Shaders.h>
#include <engine/text/TextRenderer.h>
#include <engine/textures/Texture.h>
#include <engine/widgets/Colors.h>
#include <engine/widgets/drawables/Drawable.h>
#include <engine/input/Input.h>
#include "common.h"

namespace GEngine {
    namespace Widgets {
        namespace Drawables {
            static GEngine::Shader* db_shaders = nullptr;
            static GEngine::Text::TextRenderer* db_text = nullptr;
            class Button : public Drawable {
                using OnClickEvent = std::function<void(int x, int y)>;

                public:
                Button(GEngine::MVP* mvp, Rect shape, std::string text, std::string fontname, int wPx, int hPx, Colors::Color fill_color, float border = 1, Colors::Color border_color = Colors::cl_white);
                Button(GEngine::MVP* mvp, Rect shape, std::string text, std::string fontname, int wPx, int hPx, std::string background_img, float border = 1, Colors::Color border_color = Colors::cl_white);
                Button(void);
                ~Button(void);

                void render(void) override;
                void tick(void) override;
                void destroy(void) override;

                bool eventHandler(Event* evt) override;

                void setText(std::string text);
                void setFont(std::string name);
                void setBorderSize(int size);
                void setFillColor(Colors::Color color);
                void setBorderColor(Colors::Color color);

                void setOnRightClick(OnClickEvent& func);
                void setOnLeftClick(OnClickEvent& func);

                private:
                void initShaders(void);
                void initBuffers(void);
                void initTextRenderer(void);

                private:
                OnClickEvent mRightClick;
                OnClickEvent mLeftClick;

                int mBorderSize = 0;
                Colors::Color mFillColor;
                Colors::Color mBorderColor;

                std::string mText;
                std::string mFontName;
                int mTextWPx = 0;
                int mTextHPx = 0;

                GEngine::Texture* mTexture = nullptr;

                GEngine::VBO* mVBO = nullptr;
                GEngine::VAO* mVAO = nullptr;
                GEngine::IBO* mIBO = nullptr;

                GLfloat *mVertices = nullptr;
                GLubyte *mIndices = nullptr;

                GEngine::FrameBuffer* mFBO = nullptr;

                GEngine::MVP *mMVP = nullptr;
            };
        }  // namespace Drawables
    }  // namespace Widgets

}  // namespace GEngine
