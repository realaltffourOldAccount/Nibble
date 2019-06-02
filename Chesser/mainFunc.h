/**
 * @file mainFunc.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Declares the cross-platform system's main function.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#include "common.h"

// Struct containing main function data to pass.
struct MainData {
#if defined(__ANDROID__)
	GLFMDisplay* display;
#elif defined(__WINDOWS__)
	HINSTANCE instance;
	HINSTANCE instance2;
	PSTR pstr;
	INT i;
#endif
	int argc = 0;
	char** argv = nullptr;
};

// Our Main Function
int __main(MainData* data);

// Cross-Platform Main Function
#if defined(__WINDOWS__)
#if !defined(__DEBUG__)
INT WinMain(HINSTANCE instance, HINSTANCE instace2, PSTR pstr, INT i) {
	MainData* data = new MainData;
	data->instance = instance;
	data->instance2 = instance2;
	data->pstr = pstr;
	data->i = i;
	return __main(data);
}
#else
int main(int argc, char** argv) {
	MainData* data = new MainData;
	data->argc = argc;
	data->argv = argv;
	return __main(data);
}
#endif
#elif defined(__ANDROID__)
void glfmMain(GLFMDisplay* display) {
	MainData* data = new MainData;
	data->display = display;
	__main(data);
}
#else
int main(int argc, char** argv) {
	MainData* data = new MainData;
	data->argc = argc;
	data->argv = argv;
	return __main(data);
}
#endif
