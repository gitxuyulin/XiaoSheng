//
// Created by 徐玉林 on 2019-11-04.
//

#include <jni.h>
#include <android/log.h>

jobjectArray getStrings(JNIEnv *env, jobject obj, jint count, jstring sample) {

    const char *c_str_sample = NULL;
    jclass cls_string = NULL;

    //保证至少可以创建3个局部引用（str_array,cls_string,obj_str）
    if ((*env)->EnsureLocalCapacity(env, 3) != JNI_OK) {
        return NULL;
    }

    c_str_sample = (*env)->GetStringUTFChars(env, sample, NULL);
    if (c_str_sample == NULL) {
        return NULL;
    }

    cls_string = (*env)->FindClass(env, "java/lang/String");
    if (cls_string == NULL) {
        return NULL;
    }
}

static jclass g_cls_OOMActivity = NULL;
const JNINativeMethod g_methods[] = {"getStrings", "(ILjava/lang/String;)[Ljava/lang/String;",
                                     (void *) getStrings};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "初始化");
    JNIEnv *env = NULL;
    jclass cls = NULL;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    //查找要加载的本地方法class引用
    cls = (*env)->FindClass(env, "example/xuyulin/cash/OOMActivity");
    if (cls == NULL) {
        return JNI_ERR;
    }

    //将class的引用缓存到全局变量中
    g_cls_OOMActivity = (*env)->NewWeakGlobalRef(env, cls);
    //手动删除局部引用
    (*env)->DeleteLocalRef(env, cls);

    //将java中的native方法与本地函数绑定
    (*env)->RegisterNatives(env, g_cls_OOMActivity, g_methods,
                            sizeof(g_methods) / sizeof(g_methods[0]));

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "销毁");
    JNIEnv *env = NULL;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    (*env)->UnregisterNatives(env, g_cls_OOMActivity);
    (*env)->DeleteWeakGlobalRef(env, g_cls_OOMActivity);
}