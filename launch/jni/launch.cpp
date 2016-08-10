#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "launch.h"

void TipThread(void *procname)
{
	while(1)
	{
		printf("[+] wait %s...\n", (char *)procname);
		sleep(1);
	}
}

int main(int argc, char *argv[])
{	
	pid_t pid=0;
	NDKINJECT inj;
	pthread_t idtip;
	
	//参数检测
	if (argc<3)
	{
		printf("UseAge:\n\t%s ProcessName LibToInject <LibGame>\n\n", argv[0]);
		return 0;
	}
	
	// 检查so是否存在
	if (access(argv[2], R_OK) != 0)
	{
		printf("[+] err: lib to inject must exist...\n\n");
		return 0;
	}

	// 提示线程
	pthread_create(&idtip, NULL, (void* (*)(void*))&TipThread, (void *)argv[1]);
	
	//等待进程
	while(pid==0)
	{
		pid = inj.find_pid_of(argv[1]);
		usleep(100000);
	}
	
	// 开始注入
	if (argc==3)
	{
		if (inj.inject_remote_process(pid, (const char *)argv[2], "so_entry", NULL, 0, 0) != 1)
		{
			printf("[+] err: inject %s to %s faild...\n\n", argv[2], argv[1]);
			return 0;
		}
	}
	else if (argc==4)
	{
		if (inj.inject_remote_process(pid, (const char *)argv[2], "so_entry", (const char *)argv[3], strlen(argv[3]), 0) != 1)
		{
			printf("[+] err: inject %s to %s faild...\n\n", argv[2], argv[1]);
			return 0;
		}
	}
	else
	{
		printf("[+] err: params num not match\n\n");
		return 0;
	}

	printf("[+] launch success...\n\n");
	
	return 1;
}