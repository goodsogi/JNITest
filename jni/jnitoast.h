#include <jni.h>

#ifndef _addvals_h
#define _addvals_h
#ifndef _cplusplus
extern "C" {
#endif

#ifndef NELEM
#define NELEM(x) ((int)(sizeof(x)/sizeof((x)[0])))
#endif

void displayToast(JNIEnv* env, jobject thiz, jobject charseq);

#ifdef _cplusplus
}

#endif
#endif
