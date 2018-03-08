//
// Created by eXpert on 3/7/2018.
//
#include "PluginLoaderJni.h"
#include "PluginLoader.h"
#include "handle.h"

PluginLoader* PluginLoader::instance;
/*
 * Class:     com_spartan2015_PluginLoader
 * Method:    init
 * Signature: ()V
 */
void Java_com_spartan2015_PluginLoader_init
        (JNIEnv *env, jobject obj)
{
    PluginLoader *pluginLoader = PluginLoader::getInstance();
    setHandle(env, obj, pluginLoader);
}

/*
 * Class:     com_spartan2015_PluginLoader
 * Method:    loadPluginNative
 * Signature: (Ljava/lang/String;F)J
 */
jlong Java_com_spartan2015_PluginLoader_loadPluginNative
        (JNIEnv *env, jobject object, jstring key, jfloat rate)
{
    PluginLoader *pluginLoader =
            getHandle<PluginLoader>(env,object);
    const char *keyAsChar = env->GetStringUTFChars(key,0);
    Plugin *plugin = pluginLoader->loadPlugin(keyAsChar,rate);
    env->ReleaseStringUTFChars(key,keyAsChar);
    return (jlong)plugin;
}