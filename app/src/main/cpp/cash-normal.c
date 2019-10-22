//
// Created by 徐玉林 on 2019-10-22.
//
#include <jni.h>
#include <android/log.h>

//使用时缓存
void Java_example_xuyulin_cash_CacheActivity_accessField(JNIEnv *env, jobject thiz) {

    jclass cls_cash;
    static jfieldID fie_str = NULL;
    jstring j_str;
    const char *c_str;

    // 获取该对象的Class引用
    cls_cash = (*env)->GetObjectClass(env, thiz);
    if (cls_cash == NULL)return;

    // 先判断字段ID之前是否已经缓存过，如果已经缓存过则不进行查找
    if (fie_str == NULL) {
        fie_str = (*env)->GetFieldID(env, cls_cash, "str", "Ljava/lang/String;");
        if (fie_str == NULL)return;
    }

    // 获取字段的值
    j_str = (*env)->GetObjectField(env, thiz, fie_str);
    c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
    if (c_str == NULL)return;

    __android_log_print(ANDROID_LOG_ERROR, "xyl", "字符串=%s", c_str);
    (*env)->ReleaseStringUTFChars(env, j_str, c_str);

    //修改字符串的值
    j_str = (*env)->NewStringUTF(env, "这次底层c语言");
    if (j_str == NULL)return;

    (*env)->SetObjectField(env, thiz, fie_str, j_str);

    //释放本地引用
    (*env)->DeleteLocalRef(env, cls_cash);
    (*env)->DeleteLocalRef(env, j_str);
}

jstring
Java_example_xuyulin_cash_CacheActivity_newString(JNIEnv *env, jobject thiz, jcharArray j_char_arr,
                                                  jint length) {
    static jclass cls_string = NULL;
    static jmethodID jm_string = NULL;
    jchar *chars = NULL;
    jcharArray elemArray;
    jstring j_str = NULL;

    // 注意：这里缓存局引用的做法是错误，这里做为一个反面教材提醒大家，下面会说到。
    //但是请注意：cls_string是一个局部引用，与方法和字段ID不一样，
    // 局部引用在函数结束后会被VM自动释放掉，这时cls_string成为了一个野针对
    //（指向的内存空间已被释放，但变量的值仍然是被释放后的内存地址，不为NULL），
    // 当下次再调用Java_com_xxxx_newString这个函数的时候，会试图访问一个无效的局部引用，
    // 从而导致非法的内存访问造成程序崩溃。所以在函数内用static缓存局部引用这种方式是错误的。
    // 下篇文章会介绍局部引用和全局引用，利用全局引用来防止这种问题，请关注。
    if (cls_string == NULL) {
        cls_string = (*env)->FindClass(env, "java/lang/String");
        if (cls_string == NULL)return NULL;
    }

    //缓存Stirng的构造方法
    if (jm_string == NULL) {
        jm_string = (*env)->GetMethodID(env, cls_string, "<init>", "([C)V");
        if (jm_string == NULL)return NULL;
    }

    __android_log_print(ANDROID_LOG_ERROR, "xyl", "c中获取的数组的长度:%d", length);
    elemArray = (*env)->NewCharArray(env, length);
    if (elemArray == NULL)return NULL;

    // 获取数组的指针引用，注意：不能直接将jcharArray作为SetCharArrayRegion函数最后一个参数
    chars = (*env)->GetCharArrayElements(env, j_char_arr, NULL);
    if (chars == NULL)return NULL;

    // 将Java字符数组中的内容复制指定长度到新的字符数组中
    (*env)->SetCharArrayRegion(env, elemArray, 0, length, chars);

    // 调用String对象的构造方法，创建一个指定字符数组为内容的String对象
    j_str = (*env)->NewObject(env, cls_string, jm_string, elemArray);

    // 释放本地引用
    (*env)->DeleteLocalRef(env, elemArray);

    return j_str;
}

jmethodID MID_Cash_callBack;

//类静态初始化缓存
void Java_example_xuyulin_cash_CacheActivity_initIDs(JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "初始化");
    MID_Cash_callBack = (*env)->GetMethodID(env, clazz, "callBack", "()V");
}

void Java_example_xuyulin_cash_CacheActivity_nativeMethod(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "调用");
    (*env)->CallVoidMethod(env, thiz, MID_Cash_callBack);
}



