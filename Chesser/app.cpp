#include "defs.h"
// Our Main Function
int __main(int argc, char* argv[]);

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if defined(__DEBUG__)
#include <windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT) { return __main(0, nullptr); }
#else
int main(int argc, char* argv[]) { return __main(argc, argv); }
#endif
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
#else
    App(void) : Window() {
#endif
        this->setEventHandler(eventHandle);
        object = new GEngine::Object("assets/awesomeface.png",
                                     GEngine::Rect(50, 50, 100, 100));
        mvp = new GEngine::MVP();
        proj = glm::ortho(0.0f, float(this->getState()._win_width), 0.0f,
                          float(this->getState()._win_height));
        mvp->updateProj(proj);

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
        shader = new GEngine::Shader("glsl/tex_vs.glsl", "glsl/tex_fs.glsl");
#else
        shader =
            new GEngine::Shader("glsl/tex_vs_es.glsl", "glsl/tex_fs_es.glsl");
#endif
    };
    ~App(void) {}

  public:
    void OnKey(int key, int scancode, int action, int mods) {}
    void OnMouseButton(int button, int action, int mods) {}

    void eventHandler(GEngine::Event& evt) {}

  public:
    void tick(void) {}
    void render(void) {
        shader->bind();
        mvp->bind(shader->getProgId());
        object->bind(0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};
static App* app = nullptr;
void eventHandle(GEngine::Event& evt) { /*app->eventHandler(evt);*/
}

int __main(int argc, char* argv[]) {
    initApp(argc, argv);

    App _app;
    app = &_app;
    _app.start();

    return 0;
}
