//#include "Game.h"
//
// static GEngine::Object* object;
// static GEngine::MVP* mvp;
// static GEngine::Shader* shader;
//
// static glm::mat4 proj;
//#ifndef __ANDROID__
// Game::Game() : Window(false, WINDOW_WIDTH, WINDOW_HEIGHT, "Chesser") {
//#else
// Game::Game() : Window() {
//#endif
//    object = new GEngine::Object("assets/awesomeface.png",
//                                 GEngine::Rect(50, 50, 100, 100));
//    mvp = new GEngine::MVP();
//    proj = glm::ortho(0.0f, float(this->getState()._win_width), 0.0f,
//                      float(this->getState()._win_height));
//    mvp->updateProj(proj);
//
//#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
//    shader = new GEngine::Shader("glsl/tex_vs.glsl", "glsl/tex_fs.glsl");
//#else
//    shader = new GEngine::Shader("glsl/tex_vs_es.glsl",
//    "glsl/tex_fs_es.glsl");
//#endif
//}
//
// Game::~Game() {}
//
// void Game::OnKey(int key, int scancode, int action, int mods) {}
//
// void Game::OnMouseButton(int button, int action, int mods) {}
//
// void Game::tick(void) {}
// void Game::render(void) {
//    shader->bind();
//    mvp->bind(shader->getProgId());
//    object->bind(0);
//
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//}
//