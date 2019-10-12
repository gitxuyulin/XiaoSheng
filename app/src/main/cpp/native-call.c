//
// Created by 徐玉林 on 2019-08-13.
//


#include <jni.h>
#include <android/log.h>
#include "name.h"

void Java_example_xuyulin_xiaosheng_NativeCallPresent_callJavaCommonMethod(JNIEnv *env,
                                                                           jclass cls) {

    /**
    * 获取类的默认构造方法id
    * */
    const char *method = "<init>";
    jmethodID mid_construct = (*env)->GetMethodID(env, cls, method, "()V");
    if (mid_construct == NULL) {
        return;
    }

    /**
    * 查找实例方法的id
     *
     * 获取构造方法ID，方法名称使用"<init>"
     * 方法签名的格式为：(形参参数类型列表)返回值。形参参数列表中，
     * 引用类型以L开头，后面紧跟类的全路径名（需将.全部替换成/），以分号结尾。
     * Z-boolean
     * B-byte
     * C-char
     * S-short
     * I-int
     * J-long
     * F-float
     * D-double
    * */
    jmethodID mid_instance = (*env)->GetMethodID(env, cls, "methodCommon",
                                                 "(Ljava/lang/String;I)V");
    if (mid_instance == NULL) {
        return;
    }

    /**
    * 创建该类的实例
    * */
    jobject job = (*env)->NewObject(env, cls, mid_construct);
    if (job == NULL) {
        return;
    }

    /**
    * 调用对象的实例方法
    * */
    jstring str = (*env)->NewStringUTF(env, "我来自遥远的c++");
    (*env)->CallVoidMethod(env, job, mid_instance, str, 3000);

    (*env)->DeleteLocalRef(env, job);
    (*env)->DeleteLocalRef(env, str);
}

void Java_example_xuyulin_xiaosheng_NativeCallPresent_callJavaStaticMethod(JNIEnv *env,
                                                                           jclass cls) {
    /**
    * 1.获取class对象
    * */
//    jclass clazz = NULL;
//    clazz = (*env)->FindClass(env, "example.xuyulin.xiaosheng.NativeCallPresent");
//    if (clazz = NULL) {
//        return;
//    }

    /**
     * 2.从class中查找staticmethod
     * */
    jmethodID mid_static_method;
    mid_static_method = (*env)->GetStaticMethodID(env, cls, "methodStatic",
                                                  "(Ljava/lang/String;I)V");
    if (mid_static_method == NULL) {
        return;
    }

    /**
     * 3.调用staticmethod
     * */
    jstring str_arg = NULL;
    str_arg = (*env)->NewStringUTF(env, "我来自遥远的c++");
    (*env)->CallStaticVoidMethod(env, cls, mid_static_method, str_arg, 5);

    (*env)->DeleteLocalRef(env, str_arg);
}

void Java_example_xuyulin_xiaosheng_MainActivity_accessInstaceField(JNIEnv *env, jclass cls,

                                                                    jobject user_bean) {
    jclass clazz;
    jfieldID fid;
    jstring j_str;
    jstring j_newStr;
    const char *c_str = NULL;

    clazz = (*env)->GetObjectClass(env, user_bean);
    if (clazz == NULL)
        return;

    fid = (*env)->GetFieldID(env, clazz, "name", "Ljava/lang/String;");
    if (fid == NULL)return;

    j_str = (*env)->GetObjectField(env, user_bean, fid);

    c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
    if (c_str == NULL)return;

    __android_log_print(ANDROID_LOG_ERROR, "xyl", "姓名=%s", c_str);

    (*env)->ReleaseStringChars(env, j_str, c_str);

    j_newStr = (*env)->NewStringUTF(env, "大师");
    if (j_newStr == NULL)return;

    (*env)->SetObjectField(env, user_bean, fid, j_newStr);

    (*env)->DeleteLocalRef(env, j_str);
    (*env)->DeleteLocalRef(env, j_newStr);
}

void Java_example_xuyulin_xiaosheng_MainActivity_accessStaticField(JNIEnv *env, jclass cls,
                                                                   jobject user_bean) {

    jclass clazz;
    jfieldID fid;
    jstring j_sex;
    const char *c_sex = NULL;
    jstring j_newSex;

    clazz = (*env)->GetObjectClass(env, user_bean);
    if (clazz == NULL)
        return;

    fid = (*env)->GetStaticFieldID(env, clazz, "sex", "Ljava/lang/String;");
    if (fid == NULL)return;

    j_sex = (*env)->GetStaticObjectField(env, clazz, fid);
    c_sex = (*env)->GetStringUTFChars(env, j_sex, NULL);
    __android_log_print(ANDROID_LOG_ERROR, "xyl", "性别=%s", c_sex);
    (*env)->ReleaseStringChars(env, j_sex, c_sex);

    j_newSex = (*env)->NewStringUTF(env, "女");
    if (j_newSex == NULL)
        return;

    (*env)->SetStaticObjectField(env, clazz, fid, j_newSex);

    (*env)->DeleteLocalRef(env, j_sex);
    (*env)->DeleteLocalRef(env, j_newSex);
}