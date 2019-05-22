#define THROW_ERROR(msg) \
	Log::error(msg);     \
	__err_check();

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

#define BIT(x) (1 << x)