//
// Created by 徐玉林 on 2019-07-31.
//



#include <malloc.h>
#include <cstring>
#include "name.h"

jstring return_my_name(JNIEnv *env, jstring name) {
    const char *myName = env->GetStringUTFChars(name, NULL);
    return env->NewStringUTF(myName);
}

jint get_intarray_region_sum(JNIEnv *env, jintArray j_array) {
    jint arraySize;
    jint *c_rray;
    jint sum = 0, i = 0;
    arraySize = env->GetArrayLength(j_array);
    c_rray = (jint *) malloc(sizeof(jint) * arraySize);
    memset(c_rray, 0, sizeof(jint) * arraySize);
    env->GetIntArrayRegion(j_array, 0, arraySize, c_rray);
    for (i = 0; i < arraySize; i++) {
        sum += c_rray[i];
    }
    free(c_rray);
    return sum;
}

jint get_intarray_element_sum(JNIEnv *env, jintArray j_array) {
    jint sum = 0, i = 0;
    jint arr_len;
    jint *c_array;
    arr_len = env->GetArrayLength(j_array);
    c_array = env->GetIntArrayElements(j_array, NULL);
    if (c_array == NULL) {
        return NULL;
    }
    for (int i = 0; i < arr_len; ++i) {
        sum += c_array[i];
    }
    env->ReleaseIntArrayElements(j_array, c_array, 0);
    return sum;
}

jint get_intarray_primitive_sum(JNIEnv *env, jintArray j_array) {
    jint sum = 0, i;
    jint arr_len;
    jint *c_array;
    arr_len = env->GetArrayLength(j_array);
    c_array = (jint *) env->GetPrimitiveArrayCritical(j_array, NULL);
    if (c_array == NULL) {
        return NULL;
    }
    for (i = 0; i < arr_len; ++i) {
        sum += *(c_array + i);
    }
    env->ReleasePrimitiveArrayCritical(j_array, c_array, 0);
    return sum;
}

jobjectArray get_objectarray(JNIEnv *env, jobject obj, jint size) {
    jobjectArray objArray;
    jclass cls;
    const char *clssStr = "[I";
    cls = env->FindClass(clssStr);
    if (cls == NULL) {
        return NULL;
    }
    objArray = env->NewObjectArray(size, cls, NULL);

    for (int i = 0; i < size; ++i) {
        jintArray intArray = env->NewIntArray(size);
        jint buffer[256];
        if (intArray == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            buffer[j] = j;
        }
        env->SetIntArrayRegion(intArray, 0, size, buffer);
        env->SetObjectArrayElement(objArray, i, intArray);
        env->DeleteLocalRef(intArray);
    }
    return objArray;
}
