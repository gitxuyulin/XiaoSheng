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
    (*env)->DeleteLocalRef(env,cls_cash);
    (*env)->DeleteLocalRef(env,j_str);
}



