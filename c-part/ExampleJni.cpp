//
// Created by eXpert on 3/7/2018.
//

#include "ExampleJni.h"
#include "library.h"

jchar Java_com_spartan2015_ExampleJni_hello(JNIEnv *, jclass)
{
    return (jchar)hello();
}