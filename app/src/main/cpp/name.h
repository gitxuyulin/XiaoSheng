//
// Created by 徐玉林 on 2019-07-31.
//



#ifndef XIAOSHENG_NAME_H
#define XIAOSHENG_NAME_H

//#include <string>
#include <jni.h>


jstring return_my_name(JNIEnv *env, jstring name);

jint get_intarray_region_sum(JNIEnv *env, jintArray jintArray1);

jint get_intarray_element_sum(JNIEnv *env, jintArray j_array);

jint get_intarray_primitive_sum(JNIEnv *env,jintArray j_array);

jobjectArray get_objectarray(JNIEnv *env, jobject obj, jint size);


#endif //XIAOSHENG_NAME_H
