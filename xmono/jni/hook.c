#include <dlfcn.h>
#include "hook.h"
#include "log.h"

MSHookFunction(void *symbol, void *hook, void **old)
{
	void *plibhook = dlopen("/data/local/tmp/libsubstrate.so", RTLD_LAZY);
	if (plibhook==0)
	{
		LOGD("dlopen libsubstrate.so failed...");
		return;
	}

	typedef void (*PMSHookFunction)(void *symbol, void *hook, void **old);
	PMSHookFunction msHookFunction=(PMSHookFunction)dlsym(plibhook, "MSHookFunction");
	msHookFunction(symbol, hook, old);
	
	dlclose(plibhook);
}