/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class MainClass */

#ifndef _Included_MainClass
#define _Included_MainClass
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     MainClass
 * Method:    helloWorld
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MainClass_helloWorld
  (JNIEnv *, jobject);

/*
 * Class:     MainClass
 * Method:    registerCallback
 * Signature: (LMainClass/Callback;)I
 */
JNIEXPORT jint JNICALL Java_MainClass_registerCallback
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MainClass
 * Method:    callRegisteredCallback
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_MainClass_callRegisteredCallback
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif