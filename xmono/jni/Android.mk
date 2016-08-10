LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_STATIC_LIBRARIES := libmonosgen-2.0
LOCAL_MODULE    := xmono
LOCAL_SRC_FILES := xmono.c mapfile.c mono.c hooktrace.c process.c hook.c internalcall.c
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

