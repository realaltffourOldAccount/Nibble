/**
 * @file app.cpp
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the app's main function.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#include "mainFunc.h"

#include "chsr_api.h"
#include "common.h"
#include "game/Game.h"
#include "globals.cpp"

static MainData* app_data = nullptr;

static GEngine::Object* object;
static GEngine::Object* object2;
static GEngine::Shader* shader;
GEngine::Text::TextRenderer* texter;

class App : public GEngine::Window::Window {
   public:
#if !defined(__ANDROID__)
	App(void) : Window(false, WINDOW_WIDTH, WINDOW_HEIGHT, "Chesser") {
#else
	App(GLFMDisplay* display)
		: Window(display){
#endif
	};
	~App(void) {}

   public:
	void OnKey(int key, int scancode, int action, int mods) {}
	void OnMouseButton(int button, int action, int mods) {}

	void eventHandler(const GEngine::Event& evt) { Log::info(evt.ToString()); }

   public:
	void tick(void) override {
		object->translate(glm::vec2(100.0f / 128.0f, 0.0f));
	}
	void render(void) override {
		texter->RenderText("MSPF: " + std::to_string(this->getMSPF()) +
							   " UT: " + std::to_string(this->getUT()),
						   "Arial", 1.0f, GEngine::Point(0, 0),
						   glm::vec3(1.0f, 1.0f, 1.0f), this->getMVP());

		shader->bind();
		this->getMVP()->updateModel(object->getModel());
		this->getMVP()->bind(shader->getProgId());
		object->bind();
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}

   private:
	bool inited = false;
	void init(void) override {
		using namespace std::placeholders;
		this->setEventHandler(std::bind(&App::eventHandler, this, _1));

		object = new GEngine::Object("assets/awesomeface.png",
									 GEngine::Rect(100, 100, 50, 50));
		object2 = new GEngine::Object("assets/awesomeface.png",
									  GEngine::Rect(200, 250, 100, 100));

		texter = new GEngine::Text::TextRenderer();
		texter->Init();
		texter->LoadFont("Arial", "assets/fonts/arial.ttf");
		texter->LoadCharacters("Arial");

#if defined(__DESKTOP__)
		shader = new GEngine::Shader("glsl/vs.glsl", "glsl/fs.glsl");
#elif defined(__WEB__)
		shader =
			new GEngine::Shader("glsl/vs_es_em.glsl", "glsl/fs_es_em.glsl");
#elif defined(__ANDROID__)
	shader = new GEngine::Shader("glsl/vs_es.glsl", "glsl/fs_es.glsl");
#endif
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
