/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_sssm_jt_raw_socket_JtIcmpSocket */

#ifndef _Included_de_sssm_jt_raw_socket_JtIcmpSocket
#define _Included_de_sssm_jt_raw_socket_JtIcmpSocket
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_sssm_jt_raw_socket_JtIcmpSocket
 * Method:    _open
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1open
  (JNIEnv *, jobject);

/*
 * Class:     de_sssm_jt_raw_socket_JtIcmpSocket
 * Method:    _recvfrom
 * Signature: (I)Lde/sssm/jt/raw/socket/JtDatagramPacket;
 */
JNIEXPORT jobject JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1recvfrom
  (JNIEnv *, jobject, jint);

/*
 * Class:     de_sssm_jt_raw_socket_JtIcmpSocket
 * Method:    _setTimeOut
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1setTimeOut
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     de_sssm_jt_raw_socket_JtIcmpSocket
 * Method:    _ping
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1ping
  (JNIEnv *, jobject, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
