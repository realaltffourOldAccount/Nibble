#include "Label.h"

GEngine::Text::TextRenderer* dl_textRenderer =
new GEngine::Text::TextRenderer();

namespace GEngine {
    namespace Widgets {
        namespace Drawables {

            Label::Label(GEngine::Rect shape, MVP* mvp, std::string str, std::string font,
                    std::string fontpath, glm::vec3 color)
                : Drawable(shape) {
                    this->_mvp = mvp;
                    this->mText = str;
                    this->mFont = font;
                    this->mFontPath = fontpath;
                    this->mColor = color;

                    dl_textRenderer->Init();

                    dl_textRenderer->LoadFont(this->mFont, this->mFontPath, this->mRect.w,
                            this->mRect.h);
                    dl_textRenderer->LoadCharacters(this->mFont);
                }

            void Label::render(void) {
                auto mvpbackup = this->_mvp->getMVP();
                this->_mvp->updateModel(this->mModel);
                dl_textRenderer->RenderText(this->mText, this->mFont, 1.0f,
                        GEngine::Point(this->mRect.x, this->mRect.y),
                        this->mColor, this->_mvp);
                this->_mvp->updateMVP(mvpbackup);
            }

            void Label::tick(void) {}
            void Label::destroy(void) {}

            bool Label::eventHandler(Event* evt) { return true; }

            void Label::setText(std::string str) { this->mText = str; }

        }  // namespace Drawables
    }  // namespace Widgets
}  // namespace GEngine
