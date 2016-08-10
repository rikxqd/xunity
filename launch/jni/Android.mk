LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS	+=	-L$(SYSROOT)/usr/lib -llog 

LOCAL_CPP_EXTENSION	:=	.cpp

LOCAL_MODULE	:= launch

LOCAL_SRC_FILES	:= launch.cpp

LOCAL_ARM_MODE	:= arm

include $(BUILD_EXECUTABLE)

