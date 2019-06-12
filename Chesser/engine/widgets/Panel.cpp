#include "Panel.h"

namespace GEngine {
namespace Widgets {
Panel::Panel(void) {}
Panel::Panel(std::vector<Layer*> layers) { this->mLayers = layers; }
Panel::~Panel(void) { this->destroy(); }

void Panel::render(void) {
	for (int i = 0; i < this->mLayers.size(); i++) {
		this->mLayers[i]->render();
	}
}
void Panel::tick(void) {
	for (int i = 0; i < this->mLayers.size(); i++) {
		this->mLayers[i]->tick();
	}
}
void Panel::destroy(void) {}

bool Panel::eventHandler(Event* evt) {
	bool handled = false;
	for (int i = 0; i < this->mLayers.size(); i++) {
		handled = this->mLayers[i]->eventHandler(evt);
		if (handled) return true;
	}
	return false;
}

void Panel::AddLayer(Layer* layer) { this->mLayers.push_back(layer); }
void Panel::RemoveLayer(int index) {
	this->mLayers.erase(this->mLayers.begin() + index);
}

}  // namespace Widgets
}  // namespace GEngine