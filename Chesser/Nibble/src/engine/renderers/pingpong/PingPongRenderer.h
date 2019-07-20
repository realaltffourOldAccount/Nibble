/**
 * @file PingPongRenderer.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definiton of a ping pong buffer renderer.
 * @version 0.1
 * @date 2019-July-16
 *
 */


#ifndef PINGPONGRENDERER_H
#define PINGPONGRENDERER_H

#include "common.h"
#include "error_macros.h"

#include <engine/buffers/fb/FrameBuffer.h>

namespace GEngine {
    namespace Renderers {
        class PingPongRenderer {
            public:
                PingPongRenderer(int w, int h, bool depth, bool stencil);
                PingPongRenderer(GEngine::FrameBuffer* fb1, GEngine::FrameBuffer* fb2);
                ~PingPongRenderer(void);

                void render(void);
                void tick(void);
                void destroy(void);

                GEngine::FrameBuffer* getDestinationFB(void);
                GEngine::FrameBuffer* getSourceFB(void);
                void switchFrames(void);

                GEngine::FrameBuffer* getFB1(void);
                GEngine::FrameBuffer* getFB2(void);

            private:
                void __init(int w, int h, bool depth, bool stencil);

                GEngine::FrameBuffer* fb1 = nullptr;
                GEngine::FrameBuffer* fb2 = nullptr;
                bool fb1_drawTurn = true;
        };
    }
}
#endif
