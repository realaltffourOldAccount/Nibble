/**
 * @file Label.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains the definition of a label widget.
 * @version 0.1
 * @date 2019-06-05
 *
 */

#ifndef LABEL_H
#define LABEL_H

#include <engine/mvp/MVP.h>
#include <engine/text/TextRenderer.h>
#include <engine/widgets/drawables/Drawable.h>
#include "common.h"

extern GEngine::Text::TextRenderer* dl_textRenderer;

namespace GEngine {
    namespace Widgets {
        namespace Drawables {

            class Label : public Drawable {
                public:
                    Label(GEngine::Rect shape, MVP* mvp, std::string str, std::string font,
                            std::string fontpath, glm::vec3 color);
                    ~Label(void);

                    void render(void) override;
                    void tick(void) override;
                    void destroy(void) override;

                    bool eventHandler(Event* evt) override;

                    void setText(std::string str);

                private:
                    GEngine::MVP* _mvp;

                    std::string mText;
                    std::string mFont;
                    std::string mFontPath;
                    glm::vec3 mColor;
            };
        }  // namespace Drawables
    }  // namespace Widgets
}  // namespace GEngine

#endif
