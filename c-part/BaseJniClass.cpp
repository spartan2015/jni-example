//
// Created by eXpert on 3/7/2018.
//
#include "BaseJniClassJni.h"
#include "handle.h"

/*
 * Class:     com_spartan2015_BaseJniClass
 * Method:    destroy
 * Signature: ()V
 */
void Java_com_spartan2015_BaseJniClass_destroy
(JNIEnv *env, jobject obj)
{
    delete getHandle<void*>(env,obj);
}

