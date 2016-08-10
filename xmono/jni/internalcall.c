#include <stdio.h>
#include "internalcall.h"
#include "mono.h"
#include "mapfile.h"
#include "log.h"

void Logd(int strobj)
{
	LOGD("%s", (char *)mono_string_to_utf8(strobj));
}

int GetProcessName()
{
	char buff[1024]={0x00};
	GetCurrentProcessName(buff);
	
	int domain = mono_get_root_domain();
	if (domain==0)
	{
		return 0;
	}
	
	int ret=mono_string_new(domain, buff);
	domain=0;
	
	return ret;
}

char szImageName[260]={0x00}, szSavePath[260]={0x00};

void assembly_foreach_callback(int assembly, int userdata)
{
	int image = mono_assembly_get_image(assembly);
	if (image==0)
	{
		return;
	}
	
	char *imageName=mono_image_get_name(image);
	if (strcmp(imageName, szImageName)!=0)
	{
		return;
	}
	
	void *fp=(void *)fopen(szSavePath, "w+b");
	if (fp==0)
	{
		return;
	}
	
	fwrite(*(void **)(image+8), *(int *)(image+12), 1, fp);
	fclose(fp);
}

void Export(int imageName, int savePath)
{
	strcpy(szImageName, (char *)mono_string_to_utf8(imageName));
	strcpy(szSavePath, (char *)mono_string_to_utf8(savePath));
	mono_assembly_foreach((int)assembly_foreach_callback, 0);
}

void LoadAssembly(int path)
{
	int domain = mono_get_root_domain();
	if (domain==0)
	{
		LOGD("get root domain failed...");
		return;
	}
	// 准备加载dll，先覆盖为自定义的map函数，不能用unity的
	UseMymap();
	// 加载程序集
	mono_domain_assembly_open(domain, (char *)mono_string_to_utf8(path));
	// 释放自定义map函数，改用unity的
	UnuseMymap();
	domain=0;
}