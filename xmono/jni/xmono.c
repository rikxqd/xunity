#include <pthread.h>
#include <unistd.h>
#include <dlfcn.h>
#include "mono.h"
#include "log.h"
#include "mapfile.h"
#include "hooktrace.h"
#include "internalcall.h"
 
void mainthread()
{
	// 等待libmono.so加载
	void *pLibMono=0;
	do
	{
		pLibMono=dlopen("libmono.so", RTLD_LAZY);
		usleep(200000);
	}while(pLibMono==0);
	dlclose(pLibMono);
	// 获取所需的mono函数
	InitMonoFunction();
	// hook mono_trace，打印mono自带的一些日志
	HookTrace();
	// hook mono_map_override，保存unity的文件操作函数
	HookMapOverride();
	// 延迟下，让游戏先加载所需的dll
	sleep(10);
	// 开搞
	LOGD("------------------let's start--------------------");
	// domian用于隔离执行环境，所有程序集使用游戏创建的同一个domain
	int domain = mono_get_root_domain();
	if (domain==0)
	{
		LOGD("get root domain failed...");
		return;
	}
	// 新线程中操作domain，必须先attach
	int thread = mono_thread_attach(domain);
	if (thread==0)
	{
		LOGD("attach thread failed...");
		return;
	}
	// 准备加载xlua.dll，先覆盖为自定义的map函数，不能用unity的
	UseMymap();
	// 加载程序集
	int assembly = mono_domain_assembly_open(domain, "/data/local/tmp/Lua.dll");
	if (assembly==0)
	{
		LOGD("load assembly failed...");
		return;
	}
	// 获取image，用于查找入口函数
	int image = mono_assembly_get_image(assembly);
	if (image==0)
	{
		LOGD("get image failed...");
		return;
	}
	// 释放自定义map函数，改用unity的
	UnuseMymap();
	// 添加些internal call，用于c#与runtime交互
	mono_add_internal_call("XLUA.XLuaFramework::Logd", Logd);
	mono_add_internal_call("XLUA.XLuaFramework::GetProcessName", GetProcessName);
	mono_add_internal_call("XLUA.XLuaFramework::Export", Export);
	mono_add_internal_call("XLUA.XLuaFramework::LoadAssembly", LoadAssembly);
	// 查找入口类
	int entryclass = mono_class_from_name(image, "XLUA", "XLuaFramework");
	if (entryclass==0)
	{
		LOGD("get main class failed...");
		return;
	}
	// 查找入口函数
	int methoddesc = mono_method_desc_new("XLuaFramework::Launch", false);
	int entrymethod = mono_method_desc_search_in_class(methoddesc, entryclass);
	mono_method_desc_free(methoddesc);
	if (entrymethod==0)
	{
		LOGD("get main method failed...");
		return;
	}
	// 执行入口函数
	mono_runtime_invoke(entrymethod, NULL, NULL, NULL);
	// 释放线程对domain的访问，不然会导致gc时崩溃
	mono_thread_detach(thread);
	// 释放变量
	thread=0;
	entrymethod=0;
	domain=0;
	assembly=0;
	image=0;
	entryclass=0;
	methoddesc=0;
	pLibMono=0;
}

__attribute__ ((__constructor__))
void main()
{
	LOGD("--------------------xmono------------------");
	
	pthread_t id;
	pthread_create(&id, NULL, (void *)mainthread, NULL);
}