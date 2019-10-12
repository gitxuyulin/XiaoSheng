#include <jni.h>
#include <string>
#include <android/log.h>
#include "name.h"

extern "C" JNIEXPORT jstring JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */, jstring name) {
    std::string hello = "Hello from C++";
    const char *s_name = env->GetStringUTFChars(name, 0);
    if (s_name == NULL) {
        return NULL;
    }
    hello.append(s_name);
    env->ReleaseStringUTFChars(name, s_name);
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_getName(JNIEnv *env, jobject, jstring name) {
    jstring myName = return_my_name(env, name);
    return myName;
}

extern "C" JNIEXPORT jstring JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_getCritical(JNIEnv *env, jobject, jstring name) {
    const jchar *c_str = NULL;
    char buff[128] = "hello ";
    char *pBuff = buff + 6;
    /*
     * 在GetStringCritical/RealeaseStringCritical之间是一个关键区。
     * 在这关键区之中,绝对不能呼叫JNI的其他函数和会造成当前线程中断或是会让当前线程等待的任何本地代码，
     * 否则将造成关键区代码执行区间垃圾回收器停止运作，任何触发垃圾回收器的线程也会暂停。
     * 其他触发垃圾回收器的线程不能前进直到当前线程结束而激活垃圾回收器。
     */
    c_str = env->GetStringCritical(name, NULL);  // 返回源字符串指针的可能性
    if (c_str == NULL)  // 验证是否因为字符串拷贝内存溢出而返回NULL
    {
        return NULL;
    }
    while (*c_str) {
        *pBuff++ = *c_str++;
        __android_log_print(ANDROID_LOG_ERROR, "xyl", "数值=%c", c_str);
    }
    env->ReleaseStringCritical(name, c_str);
    return env->NewStringUTF(buff);
}

extern "C" JNIEXPORT jstring JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_getRegion(JNIEnv *env, jobject, jstring name) {
    jsize size = env->GetStringLength(name);
    char buff[128] = "hello ";
    char *cbuff = buff + 6;
    env->GetStringUTFRegion(name, 0, size, cbuff);
    return env->NewStringUTF(buff);
}

extern "C" JNIEXPORT jint JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_getArraySum(JNIEnv *env, jobject,
                                                        jintArray j_array) {
//    return get_intarray_region_sum(env, j_array);
//    return get_intarray_element_sum(env, j_array);
    return get_intarray_primitive_sum(env, j_array);
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_example_xuyulin_xiaosheng_MainActivity_getObjectArray(JNIEnv *env, jobject obj, jint size) {
    return get_objectarray(env, obj, size);
}
