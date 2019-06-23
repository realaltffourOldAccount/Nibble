/**
 * @file app.cpp
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the app's main function.
 * @version 0.2
 * @date 2019-05-31
 *
 */
#include "mainFunc.h"

#include <engine/widgets/Panel.h>
#include <engine/widgets/drawables/label/Label.h>
#include <engine/widgets/drawables/object/Object2D.h>
#include <engine/widgets/layouts/SimpleLayout.h>
#include "chsr_api.h"
#include "common.h"
#include "game/Game.h"

static MainData* app_data = nullptr;

class App : public GEngine::Window::Window {
   public:
#if !defined(__ANDROID__)
	App(void) : Window(false, WINDOW_WIDTH, WINDOW_HEIGHT, "Chesser") {
		this->init();
#else
	App(GLFMDisplay* display)
		: Window(display){
#endif
	};
	~App(void) {}

   public:
	bool eventHandler(GEngine::Event* evt) {
		// Log::info(evt->ToString(),
		//		  Log::GenLogID(__LINE__, __FILE__, "App", __func__));

		return panel->eventHandler(evt);
	}

   public:
	void tick(void) override {
		label->setText("MSPF: " + std::to_string(this->getMSPF()) +
					   " UT: " + std::to_string(this->getUT()));

		// object->translate(glm::vec2((50.0f / 128.0f), 0.0f));
		if (this->mInput->IsKeyPressed(API_INPUT_KEY_W) ||
			this->mInput->IsTouchState(API_INPUT_ANDROID_TOUCH_MOVED)) {
			object->translate(glm::vec2(0.0f, 1.0f));
		}
		if (this->mInput->IsKeyPressed(API_INPUT_KEY_S)) {
			object->translate(glm::vec2(0.0f, -1.0f));
		}
		if (this->mInput->IsKeyPressed(API_INPUT_KEY_D)) {
			object->translate(glm::vec2(1.0f, 0.0f));
		}
		if (this->mInput->IsKeyPressed(API_INPUT_KEY_A)) {
			object->translate(glm::vec2(-1.0f, 0.0f));
		}
		panel->tick();
	}
	void render(void) override { panel->render(); }

   private:
	GEngine::Widgets::Panel* panel = nullptr;
	GEngine::Widgets::Layer* layer = nullptr;
	GEngine::Widgets::Layouts::SimpleLayout* layout = nullptr;
	GEngine::Widgets::Drawables::Label* label = nullptr;
	GEngine::Widgets::Drawables::Object2D* object = nullptr;
	void init(void) override {
		using namespace std::placeholders;
		this->setEventHandler(std::bind(&App::eventHandler, this, _1));

		panel = new GEngine::Widgets::Panel();

		layer = new GEngine::Widgets::Layer();

		layout = new GEngine::Widgets::Layouts::SimpleLayout(
			GEngine::Rect(0, 0, 500, 500));

		layer->AddLayout(layout);
		layer->setCurrentLayout(0);
		panel->AddLayer(layer);

		object = new GEngine::Widgets::Drawables::Object2D(
			GEngine::Rect(100, 100, 50, 50), this->getMVP(),
			"assets/awesomeface.png");

		 label = new GEngine::Widgets::Drawables::Label(
			GEngine::Rect(0, 0, 0, 12), this->getMVP(), "", "arial",
			"assets/fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

		 layout->addDrawable(
			std::pair<std::string, GEngine::Widgets::Drawables::Drawable*>(
				"perf_label", label));
		layout->addDrawable(
			std::pair<std::string, GEngine::Widgets::Drawables::Drawable*>(
				"object1", object));
	}
};

int __main(MainData* data) {
	app_data = data;
	initApp(data->argc, data->argv);

#ifdef __ANDROID__
	App* _app = new App(data->display);
#else
	App* _app = new App();
#endif
	_app->start();

	return 0;
}
