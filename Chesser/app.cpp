#include "defs.h"
// Our Main Function
int __main(int argc, char* argv[]);

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if defined(__DEBUG__)
#include <Windows.h>
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

class App {
  public:
    void Init() { game = new Game(); }
    void Start() { game->start(); }
    void Destroy() { delete game; };

  private:
    Game* game = nullptr;
};

App g_app;
int __main(int argc, char* argv[]) {
    initApp();

    g_app.Init();
    g_app.Start();
    g_app.Destroy();

    return 0;
}
