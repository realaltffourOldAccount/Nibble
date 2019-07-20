#include "PingPongRenderer.h"

namespace GEngine {
    namespace Renderers {
        PingPongRenderer::PingPongRenderer(int w, int h, bool depth, bool stencil) {this->__init(w, h, depth, stencil);}
        PingPongRenderer::PingPongRenderer(GEngine::FrameBuffer* fb1, GEngine::FrameBuffer* fb2) {
            this->fb1 = fb1;
            this->fb2 = fb2;
        }

        PingPongRenderer::~PingPongRenderer(void) {
            this->destroy();
        }

        void PingPongRenderer::render(void) {
            this->getDestinationFB()->render();
            this->switchFrames();
        }
        void PingPongRenderer::tick(void) {}
        void PingPongRenderer::destroy(void) {
            delete fb1;
            delete fb2;
            fb1 = nullptr;
            fb2 = nullptr;
        }

        GEngine::FrameBuffer* PingPongRenderer::getDestinationFB(void) {
            if (fb1_drawTurn) return this->fb2;
            else return this->fb1;
        }
        GEngine::FrameBuffer* PingPongRenderer::getSourceFB(void) {
            if (fb1_drawTurn) return this->fb1;
            else return this->fb2;
        }
        void PingPongRenderer::switchFrames(void) {
            fb1_drawTurn = !fb1_drawTurn;
        }

        GEngine::FrameBuffer* PingPongRenderer::getFB1(void) {return this->fb1;}
        GEngine::FrameBuffer* PingPongRenderer::getFB2(void) {return this->fb2;}

        void PingPongRenderer::__init(int w, int h, bool depth, bool stencil) {
            this->fb1 = new GEngine::FrameBuffer(w, h, depth, stencil);
            this->fb2 = new GEngine::FrameBuffer(w, h, depth, stencil);
        }

    }
}
