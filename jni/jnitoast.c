#include <stdio.h>
#include <android/log.h>
#include "jnitoast.h"

#define EXPORT _attribute_((visibility("default")))
#define LOG_TAG ("jnitoast")

#define LOGD(...)((void)_android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, _VA_ARGS_))
#define LOGE(...)((void)_android_log_print(ANDROID_LOG_ERROR, LOG_TAG, _VA_ARGS_))

void
displayToast(JNIEnv* env, jobject thiz, jobject charseq)
{
	//Java: Toast toastobj= Toast.makeText(context, charseq, 0):

	//Toast 클래스를 가져온다.
	jclass toast = (*env)->FindClass(env, "android/widget/Toast");

	//Toast 클래스의 makeText 정적 메서드의 메서드 ID를 가져온다.
	jmethodID methodMakeText = (*env)->GetStaticMethodID(env, toast, "makeText",
			"(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
	if(methodMakeText == NULL) {
		LOGE("toast.makeText not Found");
		return;
	}

	//Toast.makeText(this, charseq, 0)를 실행한다.
	jobject toastobj = (*env)->CallStaticObjectMethod(env, toast, methodMakeText, thiz, charseq, 0);

	//toast.show를 실행한다
	//java: toastobj.show();
	jmethodID methodShow = (*env)->GetMethodID(env, toast, "show", "()V");
	(*env)->CallVoidMethod(env, toastobj, methodShow);
	return;

}

int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;

	LOGD("Registering %s natives\n", className);
	clazz = (*env)->FindClass(env, className);
	if(clazz == NULL) {
		LOGD("Native registration unable to find class '%s'\n", className);
		return -1;
	}
	if((*env)->RegisterNatives(env, clazz, gMethods, numMethods)<0) {
		LOGD("RegisterNatives failed for '%s'\n", className);
		return -1;
	}
	return 0;
}

static JNINativeMethod sMethods[] = {
	/*name, signature, funcPtr */
	{	"displayToast","(Ljava/lang/CharSequence;)V",(void*)displayToast},
};

EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	if((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		return result;
	}

	jniRegisterNativeMethods(env, "com/example/calljavamethodfromcexample/MainActivity", sMethods, NELEM(sMethods));
	return JNI_VERSION_1_6;
};
