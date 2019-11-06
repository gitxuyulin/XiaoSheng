//
// Created by 徐玉林 on 2019-11-05.
//

#include <jni.h>
#include <android/log.h>

JNIEXPORT void JNICALL Java_example_xuyulin_cash_ThrowActivity_doit(JNIEnv *env, jclass clazz) {


    jmethodID mid_exception = (*env)->GetStaticMethodID(env, clazz, "exceptionCallBack", "()V");
    if (mid_exception != NULL) {
        (*env)->CallStaticVoidMethod(env, clazz, mid_exception);
    }
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "native 开始调用方法java exceptionCallBack()");

    //检测JNI调用是否有引发异常
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionDescribe(env);
        (*env)->ExceptionClear(env);
        (*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/Exception"), "JNI抛出的异常");
        //native遇到崩溃不会阻止代码继续，所以会加个return，但是这里app崩溃导致后面根本没执行
//        return;
    }

    mid_exception = (*env)->GetStaticMethodID(env, clazz, "normalCallBack", "()V");
    if (mid_exception != NULL) {
        (*env)->CallStaticVoidMethod(env, clazz, mid_exception);
    }
}