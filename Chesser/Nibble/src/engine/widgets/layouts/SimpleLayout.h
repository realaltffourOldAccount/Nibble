/**
 * @file SimpleLayout.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains a simple definition of a complete layout.
 * @version 0.1
 * @date 2019-06-05
 *
 */

#ifndef SIMPLE_LAYOUT_H
#define SIMPLE_LAYOUT_H

#include <engine/widgets/drawables/drawables.h>
#include <engine/widgets/layouts/Layout.h>
#include "common.h"

namespace GEngine {
    namespace Widgets {
        namespace Layouts {
            class SimpleLayout : public Layout {
                public:
                    SimpleLayout(void);
                    SimpleLayout(std::map<std::string, Drawables::Drawable*> drawables);
                    SimpleLayout(Rect shape);
                    SimpleLayout(Rect shape,
                            std::map<std::string, Drawables::Drawable*> drawables);
                    ~SimpleLayout(void);

                    void render(void) override;
                    void tick(void) override;

                    bool eventHandler(Event* evt) override;

                    void addDrawable(std::pair<std::string, Drawables::Drawable*> item) {
                        this->mDrawables.insert(item);
                    }

                private:
                    std::map<std::string, Drawables::Drawable*> mDrawables;
            };
        }  // namespace Layouts
    }  // namespace Widgets

}  // namespace GEngine

#endif
