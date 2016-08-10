#include <unistd.h>
#include "mono.h"
#include "log.h"

pmono_get_domain mono_get_root_domain;
pmono_get_domain mono_domain_get;
pmono_domain_assembly_open mono_domain_assembly_open;
pmono_assembly_open mono_assembly_open;
pmono_jit_init mono_jit_init;
pmono_jit_exec mono_jit_exec;
pmono_assembly_get_image mono_assembly_get_image;
pmono_class_from_name mono_class_from_name;
pmono_method_desc_new mono_method_desc_new;
pmono_method_desc_search_in_class mono_method_desc_search_in_class;
pmono_method_desc_free mono_method_desc_free;
pmono_runtime_invoke mono_runtime_invoke;
pmono_jit_cleanup mono_jit_cleanup;
pmono_config_parse mono_config_parse;
pmono_main mono_main;
pmono_thread_attach mono_thread_attach;
pmono_assembly_open mono_assembly_open;
pmono_image_open_full mono_image_open_full;
pmono_assembly_open mono_image_open;
pmono_add_internal_call mono_add_internal_call;
pmono_string_to_utf8 mono_string_to_utf8;
pmono_jit_runtime_invoke mono_jit_runtime_invoke;
pmono_object_new mono_object_new;
pmono_runtime_object_init mono_runtime_object_init;
pmono_thread_detach mono_thread_detach;
pmono_string_new mono_string_new;
pmono_file_map_override mono_file_map_override;
pmono_trace mono_trace;
pmono_profiler_install mono_profiler_install;
pmono_image_get_name mono_image_get_name;
pmono_image_get_name mono_image_get_filename;
pmono_module_get_object mono_module_get_object;
pmono_assembly_foreach mono_assembly_foreach;
pmono_assembly_get_image mono_assembly_get_image;
pmono_image_create_pefile mono_image_create_pefile;

void InitMonoFunction()
 {
	void *pLibMono=dlopen("libmono.so", RTLD_LAZY);

	mono_get_root_domain = (pmono_get_domain)dlsym(pLibMono, "mono_get_root_domain");
	mono_domain_get = (pmono_get_domain)dlsym(pLibMono, "mono_domain_get");
	mono_domain_assembly_open = (pmono_domain_assembly_open)dlsym(pLibMono, "mono_domain_assembly_open");
	mono_assembly_open = (pmono_assembly_open)dlsym(pLibMono, "mono_assembly_open");
	mono_jit_init = (pmono_jit_init)dlsym(pLibMono, "mono_jit_init");
	mono_jit_exec = (pmono_jit_exec)dlsym(pLibMono, "mono_jit_exec");
	mono_assembly_get_image = (pmono_assembly_get_image)dlsym(pLibMono, "mono_assembly_get_image");
	mono_class_from_name = (pmono_class_from_name)dlsym(pLibMono, "mono_class_from_name");
	mono_method_desc_new = (pmono_method_desc_new)dlsym(pLibMono, "mono_method_desc_new");
	mono_method_desc_search_in_class = (pmono_method_desc_search_in_class)dlsym(pLibMono, "mono_method_desc_search_in_class");
	mono_method_desc_free = (pmono_method_desc_free)dlsym(pLibMono, "mono_method_desc_free");
	mono_runtime_invoke = (pmono_runtime_invoke)dlsym(pLibMono, "mono_runtime_invoke");
	mono_jit_cleanup = (pmono_jit_cleanup)dlsym(pLibMono, "mono_jit_cleanup");
	mono_config_parse = (pmono_config_parse)dlsym(pLibMono, "mono_config_parse");
	mono_main = (pmono_main)dlsym(pLibMono, "mono_main");
	mono_thread_attach=(pmono_thread_attach)dlsym(pLibMono, "mono_thread_attach");
	mono_assembly_open=(pmono_assembly_open)dlsym(pLibMono, "mono_assembly_open");
	mono_image_open_full=(pmono_image_open_full)dlsym(pLibMono, "mono_image_open_full");
	mono_image_open=(pmono_assembly_open)dlsym(pLibMono, "mono_image_open");
	mono_add_internal_call=(pmono_add_internal_call)dlsym(pLibMono, "mono_add_internal_call");
	mono_string_to_utf8=(pmono_string_to_utf8)dlsym(pLibMono, "mono_string_to_utf8");
	mono_jit_runtime_invoke=(pmono_jit_runtime_invoke)dlsym(pLibMono, "mono_jit_runtime_invoke");
	mono_object_new=(pmono_object_new)dlsym(pLibMono, "mono_object_new");
	mono_runtime_object_init=(pmono_runtime_object_init)dlsym(pLibMono, "mono_runtime_object_init");
	mono_thread_detach=(pmono_thread_detach)dlsym(pLibMono, "mono_thread_detach");
	mono_string_new=(pmono_string_new)dlsym(pLibMono, "mono_string_new");
	mono_file_map_override=(pmono_file_map_override)dlsym(pLibMono, "mono_file_map_override");
	mono_trace=(pmono_trace)dlsym(pLibMono, "mono_trace");
	mono_profiler_install=(pmono_profiler_install)dlsym(pLibMono, "mono_profiler_install");
	mono_image_get_name=(pmono_image_get_name)dlsym(pLibMono, "mono_image_get_name");
	mono_image_get_filename=(pmono_image_get_name)dlsym(pLibMono, "mono_image_get_filename");
	mono_module_get_object=(pmono_module_get_object)dlsym(pLibMono, "mono_module_get_object");
	mono_assembly_foreach=(pmono_assembly_foreach)dlsym(pLibMono, "mono_assembly_foreach");
	mono_assembly_get_image=(pmono_assembly_get_image)dlsym(pLibMono, "mono_assembly_get_image");
	mono_image_create_pefile=(pmono_image_create_pefile)dlsym(pLibMono, "mono_image_create_pefile");
	
	dlclose(pLibMono);
 }