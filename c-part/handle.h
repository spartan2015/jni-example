//
// Created by eXpert on 3/7/2018.
//

#ifndef C_HANDLE_H
#define C_HANDLE_H

#include <jni.h>

jfieldID getHandleField(JNIEnv *env, jobject obj);

template <typename T>
T *getHandle(JNIEnv *env, jobject obj)
{
    jlong handle = env->GetLongField(obj, getHandleField(env,obj));
    return reinterpret_cast<T *>(handle);
}

template <typename T>
void setHandle(JNIEnv *env, jobject obj, T *t){
    jlong handle = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, getHandleField(env,obj), handle);
}

#endif //C_HANDLE_H
