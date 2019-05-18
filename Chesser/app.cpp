#include "common.h"
// Main Function
#ifdef __ANDROID__
int __main(GLFMDisplay* display);
#else
int __main(int argc, char* argv[]);
#endif

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if defined(__DEBUG__)
#include <windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT) { return __main(0, nullptr); }
#else
int main(int argc, char* argv[]) { return __main(argc, argv); }
#endif
#elif defined(__ANDROID__)
void glfmMain(GLFMDisplay* display) { __main(display); }
#else
int main(int argc, char* argv[]) { return __main(argc, argv); }
#endif

#include "chsr_api.h"
#include "game/Game.h"
#include "globals.cpp"

void eventHandle(GEngine::Event& evt);

static GEngine::Object* object;
static GEngine::MVP* mvp;
static GEngine::Shader* shader;

static glm::mat4 proj;
class App : public GEngine::Window {
  public:
#ifndef __ANDROID__
    App(void) : Window(false, WINDOW_WIDTH, WINDOW_HEIGHT, "Chesser") {
        this->__init();
#else
    App(GLFMDisplay* display)
        : Window(display){
#endif
    };
    ~App(void) {}

  public:
    void OnKey(int key, int scancode, int action, int mods) {}
    void OnMouseButton(int button, int action, int mods) {}

    void eventHandler(GEngine::Event& evt) { Log::info(evt.ToString()); }

  public:
    void tick(void) override {}
    void render(void) override {
        shader->bind();
        mvp->bind(shader->getProgId());
        object->bind(0);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    }

  private:
    bool inited = false;
#ifndef __ANDROID__
    void __init(void){
#else
    void init(void) override {
#endif
        this->setEventHandler(eventHandle);
    object = new GEngine::Object("assets/awesomeface.png",
                                 GEngine::Rect(100, 100, 50, 50));
    mvp = new GEngine::MVP();
    proj = glm::ortho(0.0f, float(this->getState()._win_width), 0.0f,
                      float(this->getState()._win_height));
    mvp->updateProj(proj);

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
    shader = new GEngine::Shader("glsl/vs.glsl", "glsl/fs.glsl");
#elif defined(__EMSCRIPTEN__)
        shader =
            new GEngine::Shader("glsl/vs_es_em.glsl", "glsl/fs_es_em.glsl");
#elif defined(__ANDROID__)
shader = new GEngine::Shader("glsl/vs_es.glsl", "glsl/fs_es.glsl");
#endif
}
}
;

static App* app = nullptr;
void eventHandle(GEngine::Event& evt) { app->eventHandler(evt); }

#ifdef __ANDROID__
int __main(GLFMDisplay* display) {
    initApp(0, nullptr);
#else
int __main(int argc, char* argv[]) {
    initApp(argc, argv);
#endif

#ifdef __ANDROID__
    App* _app = new App(display);
    app = _app;
#else
    App _app;
    app = &_app;
#endif
    app->start();

    return 0;
}
