#include "Layer.h"

namespace GEngine {
    namespace Widgets {
        Layer::Layer(void) {}
        Layer::Layer(std::vector<Layouts::Layout*> layouts) {
            this->mLayouts = layouts;
        }
        Layer::~Layer(void) { this->destroy(); }

        void Layer::render(void) {
            if (mCurLayout) mCurLayout->render();
        }
        void Layer::tick(void) {
            if (mCurLayout) mCurLayout->tick();
        }
        void Layer::destroy(void) { mCurLayout = nullptr; }

        bool Layer::eventHandler(Event* evt) {
            if (mCurLayout) return mCurLayout->eventHandler(evt);
            return false;
        }

        void Layer::setCurrentLayout(int index) { mCurLayout = mLayouts[index]; }

        void Layer::AddLayout(Layouts::Layout* layout) {
            this->mLayouts.push_back(layout);
        }

        void Layer::RemoveLayout(int index) {
            this->mLayouts.erase(this->mLayouts.begin() + index);
        }

    }  // namespace Widgets
}  // namespace GEngine
