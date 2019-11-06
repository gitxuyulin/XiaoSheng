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
    if ((*env)->ExceptionCheck(env)) {//ExceptionCheck函数检查最近一次JNi调用是否发生了异常
        (*env)->ExceptionDescribe(env);//ExceptionDescribe函数打印这个异常的堆栈信息
        (*env)->ExceptionClear(
                env);//ExceptionClear函数清除异常堆栈信息的缓冲区（如果不清除，后面调用ThrowNew抛出的异常堆栈信息会覆盖前面的异常信息)
        (*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/Exception"),
                         "JNI抛出的异常");//ThrowNew函数手动抛出一个java.lang.Exception异常。但在JNI中抛出未捕获的异常与Java的异常处理机制不一样，在JNI中并不会立即终止本地方法的执行，而是继续执行后面的代码
        //JUN_ThrowByName(env,"java/lang/Exception","JNI抛出的异常"); 效果跟上一行一样
        //native遇到崩溃不会阻止代码继续，所以会加个return，但是这里app崩溃导致后面根本没执行
//        return;
    }

    mid_exception = (*env)->GetStaticMethodID(env, clazz, "normalCallBack", "()V");
    if (mid_exception != NULL) {
        (*env)->CallStaticVoidMethod(env, clazz, mid_exception);
    }
}

void JUN_ThrowByName(JNIEnv *env, const char *name, const char *msg) {
    // 查找异常类
    jclass cls = (*env)->FindClass(env, name);
    /* 如果这个异常类没有找到，VM会抛出一个NowClassDefFoundError异常 */
    if (cls != NULL) {
        (*env)->ThrowNew(env, cls, msg);  // 抛出指定名字的异常
    }
    /* 释放局部引用 */
    (*env)->DeleteLocalRef(env, cls);
}