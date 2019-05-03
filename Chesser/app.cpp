#include "defs.h"
// Our Main Function
int __main(int argc, char* argv[]);

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if defined(__DEBUG__)
#include <Windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT) {
    return __main(0, nullptr);
}
#else
int main(int argc, char* argv[]) {
    return __main(argc, argv);
}
#endif

#else
int main(int argc, char* argv[]) {
    return __main(argc, argv);
}
#endif

#include "game/game.h"

int __main(int argc, char* argv[]) {
    init_app();
    Log::info("Detected OS: " + std::string(os_to_str(__OS__)));

    Game game;
    game.Init();
    game.Start();
    return 0;
}

