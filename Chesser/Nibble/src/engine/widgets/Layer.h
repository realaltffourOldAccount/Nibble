/**
 * @file Layer.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definition of a layer.
 * @version 0.1
 * @date 2019-06-04
 *
 */

#ifndef LAYER_H
#define LAYER_H

#include "common.h"
#include "layouts/Layout.h"

namespace GEngine {
    namespace Widgets {
        class Layer {
            public:
                Layer(void);
                Layer(std::vector<Layouts::Layout*> layouts);
                ~Layer();

                void render(void);
                void tick(void);
                void destroy(void);

                bool eventHandler(Event* evt);

                void setCurrentLayout(int index);

                void AddLayout(Layouts::Layout* layout);
                void RemoveLayout(int index);

            private:
                std::vector<Layouts::Layout*> mLayouts;
                Layouts::Layout* mCurLayout = nullptr;
        };
    }  // namespace Widgets
}  // namespace GEngine

#endif
