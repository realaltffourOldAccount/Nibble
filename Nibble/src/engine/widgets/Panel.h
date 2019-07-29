/**
 * @file Panel.h
 * @author Ayham Mamoun (ayhamaboulalfadl@gmail.com)
 * @brief Contains the panel definition.
 * @version 0.1
 * @date 2019-06-03
 *
 */

#ifndef PANEL_H
#define PANEL_H

#include "Layer.h"
#include "common.h"
#include "layouts/layouts.h"

namespace GEngine {
    namespace Widgets {
        class Panel {
            public:
                Panel(void);
                Panel(std::vector<Layer*> layers);
                ~Panel(void);

                void render(void);
                void tick(void);
                void destroy(void);

                bool eventHandler(Event* evt);

                void AddLayer(Layer* layer);
                void RemoveLayer(int index);

            private:
                std::vector<Layer*> mLayers;
        };
    }  // namespace Widgets
}  // namespace GEngine

#endif
