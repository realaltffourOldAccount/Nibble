#include "Button.h"

namespace GEngine {
namespace Widgets {
namespace Drawables {
GEngine::Shader* db_shaders = nullptr;

Button::Button(Rect shape, std::string text, std::string fontname, int wPx,
			   int hPx, GEngine::Text::TextRenderer* tr,
			   Colors::Color fill_color, int border,
			   Colors::Color border_color) {
	this->mRect = shape;
	this->mText = text;
	this->mFontName = fontname;
	this->mFillColor = fill_color;
	this->mBorderColor = border_color;
	this->mBorderSize = border;
	this->mTextWPx = wPx;
	this->mTextHPx = hPx;

	this->initShaders();
}
Button::Button(Rect shape, std::string text, std::string fontname, int wPx,
			   int hPx, GEngine::Text::TextRenderer* tr,
			   std::string background_img, int border,
			   Colors::Color border_color) {
	this->mRect = shape;
	this->mText = text;
	this->mFontName = fontname;
	this->mBorderColor = border_color;
	this->mBorderSize = border;
	this->mTextWPx = wPx;
	this->mTextHPx = hPx;

	this->mTexture = new GEngine::Texture(background_img);

	this->initShaders();
}
Button::Button(void) {}

Button::~Button(void) {}

void Button::initShaders(void) {}

void Button::initBuffers(void) {}

bool Button::eventHandler(Event* evt) {
	if (evt->IsInCategory(GEngine::EventCategory::EventCategoryMouse)) {
		if (evt->GetEventType() == GEngine::EventType::MouseButtonPressed) {
			GEngine::MouseButtonPressedEvent* event =
				static_cast<GEngine::MouseButtonPressedEvent*>(evt);
		}
	}
}

void Button::render(void) {}
void Button::tick(void) {}
void Button::destroy(void) {}

void Button::drawBorders(int size, Colors::Color color) {}

void Button::setText(std::string text) {}
void Button::setFont(std::string name) {}
void Button::setCurveRad(int rad) {}
void Button::setBorderSize(int size) {}
void Button::setFillColor(Colors::Color color) {}
void Button::setBorderColor(Colors::Color color) {}

}  // namespace Drawables
}  // namespace Widgets
}  // namespace GEngine