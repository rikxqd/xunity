#include <sys/stat.h>
#include <unistd.h>
#include <dlfcn.h>
#include "mapfile.h"
#include "hook.h"
#include "mono.h"
#include "log.h"


int oldopenfunc, oldsizefunc, oldfdfunc, oldclosefunc, oldmapfunc, oldunmapfunc;
pmono_file_map_override old_mono_file_map_override;

void *new_mono_file_map_open(const char* name)
{
	void *ret = (void *)fopen(name, "rb");
	if (ret==0)
	{
		ret=((void* (*)(const char *))oldopenfunc)(name);
	}
	
	return ret;
}

uint64_t new_mono_file_map_size(void *fmap)
{
	struct stat stat_buf;
	if (fstat (fileno ((FILE*)fmap), &stat_buf) < 0)
	{
		return ((uint64_t (*)(void *))oldsizefunc)(fmap);
	}
	return stat_buf.st_size;
}

int new_mono_file_map_fd(void *fmap)
{
	int ret = fileno((FILE*)fmap);
	if (ret<0)
	{
		ret = ((int (*)(void*))oldfdfunc)(fmap);
	}
	
	return ret;
}

int new_mono_file_map_close(void *fmap)
{
	int ret = fclose ((FILE*)fmap);
	if (ret<0)
	{
		ret = ((int (*)(void*))oldclosefunc)(fmap);
	}
	
	return ret;
}

void *new_mono_file_map(size_t length, int flags, int fd, uint64_t offset, void **ret_handle)
{
	uint64_t cur_offset;
	size_t bytes_read;
	void *ptr = malloc(length);
	if (!ptr)
		return NULL;
	cur_offset = lseek (fd, 0, SEEK_CUR);
	if (lseek (fd, offset, SEEK_SET) != offset) {
		free (ptr);
		return NULL;
	}
	bytes_read = read (fd, ptr, length);
	lseek (fd, cur_offset, SEEK_SET);
	*ret_handle = NULL;
	return ptr;
}

int new_mono_file_unmap(void *addr, void *handle)
{
	free(addr);
	return 0;
}

void new_mono_file_map_override(int openfunc, int sizefunc, int fdfunc, int closefunc, int mapfunc, int unmapfunc)
{
	oldopenfunc = openfunc;
	oldsizefunc = sizefunc;
	oldfdfunc = fdfunc;
	oldclosefunc = closefunc;
	oldmapfunc = mapfunc;
	oldunmapfunc = unmapfunc;
	
	old_mono_file_map_override(openfunc, sizefunc, fdfunc, closefunc, mapfunc, unmapfunc);
}

void HookMapOverride()
{
	MSHookFunction(mono_file_map_override, new_mono_file_map_override, (void **)&old_mono_file_map_override);
}

void UseMymap()
{
	old_mono_file_map_override(
		(int)new_mono_file_map_open, 
		(int)new_mono_file_map_size,
		(int)new_mono_file_map_fd,
		(int)new_mono_file_map_close,
		(int)new_mono_file_map,
		(int)new_mono_file_unmap);
}

void UnuseMymap()
{
	old_mono_file_map_override(
		oldopenfunc,
		oldsizefunc,
		oldfdfunc,
		oldclosefunc,
		oldmapfunc,
		oldunmapfunc);
}