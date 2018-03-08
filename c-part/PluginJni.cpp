//
// Created by eXpert on 3/7/2018.
//
#include "PluginJni.h"
#include "Plugin.h"

/*
 * Class:     com_spartan2015_Plugin
 * Method:    getIdentifier
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_spartan2015_Plugin_getIdentifier
        (JNIEnv *env, jobject obj)
{
    Plugin *plugin = getHandle<Plugin>(env,obj);
    return env->NewStringUTF(plugin->getIdentifier().c_str());
};

/*
 * Class:     com_spartan2015_Plugin
 * Method:    getName
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_spartan2015_Plugin_getName
        (JNIEnv *env, jobject obj)
{
    Plugin *plugin = getHandle<Plugin>(env,obj);
    return env->NewStringUTF(plugin->getName().c_str());
};
/*
 * Class:     com_spartan2015_Plugin
 * Method:    getDescription
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_spartan2015_Plugin_getDescription
        (JNIEnv *env, jobject obj)
{
    Plugin *plugin = getHandle<Plugin>(env,obj);
    return env->NewStringUTF(plugin->getDescription().c_str());
};

/*
 * Class:     com_spartan2015_Plugin
 * Method:    getPluginVersion
 * Signature: ()I
 */
jint Java_com_spartan2015_Plugin_getPluginVersion
        (JNIEnv *env, jobject obj)
{
    Plugin *plugin = getHandle<Plugin>(env,obj);
    return plugin->getPluginVersion();
};