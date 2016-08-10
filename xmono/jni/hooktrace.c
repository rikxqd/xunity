#include <dlfcn.h>
#include <unistd.h>
#include "hooktrace.h"
#include "hook.h"
#include "mono.h"
#include "log.h"

//log config
char szBuffer[4096]={0x00};
int log_level=1<<6;
int log_mask=1<<0;

void my_mono_trace(int level, int mask, const char *format, ...)
{
	if (level<=log_level && (mask&log_mask))
	{
		va_list args;
		va_start (args, format);
		vsprintf(szBuffer, format, args);
		va_end (args);
		LOGD("%s", szBuffer);
	}
}

void HookTrace()
{
	int oldTrace=0;
	MSHookFunction(mono_trace, my_mono_trace, (void **)&oldTrace);
}