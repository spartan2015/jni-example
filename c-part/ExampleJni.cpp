//
// Created by eXpert on 3/7/2018.
//
#include <cstdio>
#include <string>
#include <cstring>
#include "ExampleJni.h"
#include "library.h"


jint sumWithRegion(JNIEnv *env, const _jintArray *jarray);

jchar Java_com_spartan2015_ExampleJni_hello
        (JNIEnv *env, jclass clazz)
{
    return (jchar)hello();
}

/**
 *
 * @param env
 * @param prompt
 * @return
 */
jstring getPrompt(JNIEnv *env, jstring prompt){
    const char *chars = env->GetStringUTFChars(prompt,NULL); // now this tells java to allocate mem - so OutOfMemory is possbile
    if (chars==NULL){ // but control flow will continue in native - so check if allocation failed and return early
        return NULL;//OutOfMemory already thrown
    }
    printf("%s\n",chars);
    env->ReleaseStringUTFChars(prompt,chars); // tell java you don't need the string so it can be gc'ed
    char buf[128];
    scanf("%s",buf);
    return env->NewStringUTF(buf);
}

/**
 * we allocate mem locally in buffers - so no OutOfMemoryError
 * checking is required
 *
 * @param env
 * @param str
 * @return
 */
jstring getPromptUsingRegion(JNIEnv *env, jstring str){
    jchar out[128];
    char in[128];
    int length = env->GetStringLength(str); // there is also the GetStringUTFLength returning bytes required as UTF8
    env->GetStringRegion(str, 0, length <= 127 ? length : 127, out);
    printf("%s\n",out);
    scanf("%s", in);
    return env->NewStringUTF(in); // this will tell java to create a java.lang.String (may throw OutOfMemory)
}

/**
 *  garbage collection is disabled by the current thread
 *
 * between the get critical and relese critical now threa blocking must happen
 * cause it can cause vm to deadlock - so to IO reading writting either.
 *
 * the pair must not issue blocking calls or allocate new objects in the Java virtual machine
 *
 * @param env
 * @param prompt
 * @return
 */
jstring getPromptCritical(JNIEnv *env, jstring prompt){
    const jchar *chars = env->GetStringCritical(prompt,NULL);
    if (chars==NULL){ // but control flow will continue in native - so check if allocation failed and return early
        return NULL;//OutOfMemory already thrown
    }
    env->ReleaseStringCritical(prompt,chars); // tell java you don't need the string so it can be gc'ed
    // fprintf() // would be dangerous - it is a blocking call - may deadlock the vm
    printf("%s\n",chars);
    char buf[128];
    scanf("%s",buf);
    return env->NewStringUTF(buf);
}

JNIEXPORT jstring JNICALL Java_com_spartan2015_ExampleJni_get
        (JNIEnv *env, jclass clazz, jstring string){
    return getPrompt(env, string);
}

/**
 * with region
 *
 * @param env
 * @param jarray
 * @return
 */
 jint sumWithRegion(JNIEnv *env, _jintArray *jarray) {
    int length = env->GetArrayLength(jarray);
    printf("length: %d",length);
    jint buf[length];
    env->GetIntArrayRegion(jarray,0,length,buf);
    int sum = 0;
    for(jint i = 0; i<length; i++){
        sum+=buf[i];
    }
    return sum;
}

/**
 * directo access like previous string string
 * get/release pair
 *
 * @param env
 * @param jarray
 * @return
 */
jint sumWithDirectAccess(JNIEnv *env, _jintArray *jarray) {
    int length = env->GetArrayLength(jarray);
    printf("length: %d\n",length);

    jint *elements = env->GetIntArrayElements(jarray,NULL);
    if (elements == NULL){
        /*error handling*/
        return 0;
    }
    int sum = 0;
    for(jint i = 0; i<length; i++){
        sum+=elements[i];
    }

    env->ReleaseIntArrayElements(jarray,elements,0);

    return sum;
}

/*
 * Class:     com_spartan2015_ExampleJni
 * Method:    sum
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_com_spartan2015_ExampleJni_sum
        (JNIEnv *env, jclass, jintArray jarray){
    return sumWithRegion(env, jarray);
}

void getType(JNIEnv *env, jobject obj, char * ret){
    jclass cls = env->GetObjectClass(obj);
    // First get the class object
    jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
    jobject clsObj = env->CallObjectMethod(obj, mid);
    // Now get the class object's class descriptor
    cls = env->GetObjectClass(clsObj);
    // Find the getName() method on the class object
    mid = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    // Call the getName() to get a jstring object back
    jstring strObj = (jstring)env->CallObjectMethod(clsObj, mid);
    // Now get the c string from the java jstring object
    int length = env->GetStringLength(strObj);
    env->GetStringUTFRegion(strObj,0,length, ret);
    printf("\nCalling class is: %s\n", ret);
}

/**
 *
 * @param env
 * @param prompt
 * @return
 */
void printer(JNIEnv *env, jstring prompt){
    const char *chars = env->GetStringUTFChars(prompt,NULL);
    if (chars==NULL){
        return;
    }
    printf("%s\n",chars);
    env->ReleaseStringUTFChars(prompt,chars);
}

/**
 * print int array with region
 *
 * @param env
 * @param jarray
 * @return
 */
void printer(JNIEnv *env, _jintArray *jarray) {
    int length = env->GetArrayLength(jarray);
    printf("length: %d\n",length);
    jint buf[length];
    env->GetIntArrayRegion(jarray,0,length,buf);
    for(jint i = 0; i<length; i++){
        printf("%d,",buf[i]);
    }
    printf("\n");
}

/*
 * Class:     com_spartan2015_ExampleJni
 * Method:    print
 * Signature: ([Ljava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_spartan2015_ExampleJni_print
        (JNIEnv *env, jclass, jobjectArray array){
    int length = env->GetArrayLength(array);
    for(jint i = 0; i < length; i++){
        jobject ref = env->GetObjectArrayElement(array,i);
        char *type = new char[128];
        getType(env,ref,type);
        if (strcmp("java.lang.String",type) == 0) {
            printer(env, (jstring)ref);
        }else if (strcmp("[I",type) == 0){
            printer(env, (jintArray)ref);
        }
    }
}

/**
 * create java 2 dimension array of type int[][]
 * using the jni interface
 *
 * @param env
 * @param clazz
 * @param size
 * @return
 */
jobjectArray Java_com_spartan2015_ExampleJni_initIntArray
        (JNIEnv *env, jclass clazz, jint size){
    jobjectArray result;
    jclass intArrayClazz = env->FindClass("[I");
    if (intArrayClazz==NULL)return NULL;
    result = env->NewObjectArray(size, intArrayClazz,NULL);
    if (result == NULL) return NULL;
    for(int i =0; i<size;i++){
        jintArray ar = env->NewIntArray(size);
        jint localAr[size];
        if (ar==NULL)return NULL;
        for(int j =0; j<size;j++){
            localAr[j]=i+j;
        }
        env->SetIntArrayRegion(ar,0,size,localAr);
        env->SetObjectArrayElement(result,i,ar);
        env->DeleteLocalRef(ar);
    }
    return result;
}

std::string toString(JNIEnv *env, jstring str){
    int length = env->GetStringLength(str);
    char buf[length];
    env->GetStringUTFRegion(str,0,length,buf);
    std::string s = std::string(buf);
    printf("new string: %s",s.c_str());
    return s;
}

jobject getFieldValue(JNIEnv *env,  jobject &object, jstring field) {
    jclass clazz = env->GetObjectClass(object);
    jfieldID fieldId = env->GetFieldID(clazz, toString(env, field).c_str(), "Ljava/lang/String;");
    jobject fieldValue = env->GetObjectField(object,fieldId);
    return fieldValue;
}

/*
 * Class:     com_spartan2015_ExampleJni
 * Method:    accessField
 * Signature: (Ljava/lang/String;)V
 */
void Java_com_spartan2015_ExampleJni_accessField
        (JNIEnv *env, jobject object, jstring field){
    jobject result = getFieldValue(env, object, field);
    printer(env,(jstring)result);

}