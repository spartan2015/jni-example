//
// Created by eXpert on 3/8/2018.
//
#include "handle.h"

jfieldID getHandleField(JNIEnv *env, jobject obj)
{
    jclass clazz = env->GetObjectClass(obj);
    return env->GetFieldID(clazz,"nativeHandle","J");
}