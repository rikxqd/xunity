#include <stdio.h>
#include <fcntl.h>
#include "process.h"

void GetCurrentProcessName(char *buffer)
{
	if (buffer==0x00)
	{
		return;
	}
		
	char *path[260]={0x00};
	snprintf((char *)path, 260, "/proc/%d/cmdline", getpid());
	
	int fd = open((const char*)path, O_RDONLY);
	if (fd==0)
	{
		return;
	}
	
	read(fd, (void *)buffer, 1024);
	close(fd);
}