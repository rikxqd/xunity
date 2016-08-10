#ifndef _LOG_H_
#define _LOG_H_

#include <android/log.h> 
#define LOGD(...) __android_log_print(ANDROID_LOG_INFO,"xmono",__VA_ARGS__)

#endif