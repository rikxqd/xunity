#ifndef _MAIN_H_
#define _MAIN_H_

#include <dlfcn.h>
#include <stdbool.h>
#include <fcntl.h>
 
// function define
typedef int (*pmono_main)(int argc, char* argv[]);
typedef int (*pmono_get_domain)();
typedef int (*pmono_domain_assembly_open)(int domain, const char *name);
typedef int (*pmono_assembly_open)(const char *filename, int *status);
typedef int (*pmono_jit_init)(const char *file);
typedef int (*pmono_jit_exec)(int domain, int assembly, int argc, char *argv[]);
typedef int (*pmono_assembly_get_image)(int assembly);
typedef int (*pmono_class_from_name)(int image, const char* name_space, const char *name);
typedef int (*pmono_method_desc_new)(const char *name, char include_namespace);
typedef int (*pmono_method_desc_search_in_class)(int desc, int klass);
typedef void (*pmono_method_desc_free)(int desc);
typedef int (*pmono_runtime_invoke)(int method, void *obj, void **params, int *exc);
typedef void (*pmono_jit_cleanup)(int domain);
typedef void (*pmono_config_parse)(const char *filename);
typedef int (*pmono_thread_attach)(int domain);
typedef int (*pmono_assembly_open)(const char *filename, int *status);
typedef int (*pmono_image_open_full)(const char *filename, int *status, bool refonly);
typedef void (*pmono_add_internal_call)(const char *name, const void* method);
typedef char* (*pmono_string_to_utf8)(int object);
typedef int (*pmono_jit_runtime_invoke)(int method, void *obj, void **params, int **exc, int *error);
typedef int (*pmono_object_new)(int domain, int klass);
typedef void (*pmono_runtime_object_init)(int this_obj);
typedef void (*pmono_thread_detach)(int thread);
typedef int (*pmono_string_new)(int domain, char *text);
typedef void (*pmono_file_map_override)(int openfunc, int sizefunc, int fdfunc, int closefunc, int mapfunc, int unmapfunc);
typedef void (*pmono_trace)(int level, int mask, const char *format, ...);
typedef void (*pmono_profiler_install)(int prof, int callback);
typedef char* (*pmono_image_get_name)(int image);
typedef int (*pmono_module_get_object)(int domain, int image);
typedef void (*pmono_assembly_foreach)(int func, int userdata);
typedef int (*pmono_assembly_get_image)(int assembly);
typedef int (*pmono_image_create_pefile)(int mb, void *fp, int err);

extern pmono_get_domain mono_get_root_domain;
extern pmono_get_domain mono_domain_get;
extern pmono_domain_assembly_open mono_domain_assembly_open;
extern pmono_assembly_open mono_assembly_open;
extern pmono_jit_init mono_jit_init;
extern pmono_jit_exec mono_jit_exec;
extern pmono_assembly_get_image mono_assembly_get_image;
extern pmono_class_from_name mono_class_from_name;
extern pmono_method_desc_new mono_method_desc_new;
extern pmono_method_desc_search_in_class mono_method_desc_search_in_class;
extern pmono_method_desc_free mono_method_desc_free;
extern pmono_runtime_invoke mono_runtime_invoke;
extern pmono_jit_cleanup mono_jit_cleanup;
extern pmono_config_parse mono_config_parse;
extern pmono_main mono_main;
extern pmono_thread_attach mono_thread_attach;
extern pmono_assembly_open mono_assembly_open;
extern pmono_image_open_full mono_image_open_full;
extern pmono_assembly_open mono_image_open;
extern pmono_add_internal_call mono_add_internal_call;
extern pmono_string_to_utf8 mono_string_to_utf8;
extern pmono_jit_runtime_invoke mono_jit_runtime_invoke;
extern pmono_object_new mono_object_new;
extern pmono_runtime_object_init mono_runtime_object_init;
extern pmono_thread_detach mono_thread_detach;
extern pmono_string_new mono_string_new;
extern pmono_file_map_override mono_file_map_override;
extern pmono_trace mono_trace;
extern pmono_profiler_install mono_profiler_install;
extern pmono_image_get_name mono_image_get_name;
extern pmono_image_get_name mono_image_get_filename;
extern pmono_module_get_object mono_module_get_object;
extern pmono_assembly_foreach mono_assembly_foreach;
extern pmono_assembly_get_image mono_assembly_get_image;
extern pmono_image_create_pefile mono_image_create_pefile;

void InitMonoFunction();

#endif