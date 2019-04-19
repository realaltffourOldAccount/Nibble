#include "defs.h"

// Our Main Function
int __main(int argc, char* argv[]);

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if defined(__DEBUG__)
#include <Windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT) {
    __main(0, nullptr);
    return 0;
}
#else
int main(int argc, char* argv[]) {
    __main(argc, argv);
    return 0;
}
#endif

#else
int main(int argc, char* argv[]) {
    __main(argc, argv);
    return 0;
}
#endif

int __main(int argc, char* argv[]) { return 0; }