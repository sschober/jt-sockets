#include <iostream>

#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtRawSocket.h"

#define JT_DATAGRAM_PACKET "de/sssm/jt/raw/socket/JtDatagramPacket"


JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtRawSocket__1sayHello
  (JNIEnv *env, jobject){
    std::cout << "jTomato native library" << std::endl;
}

#define ICMP 1

JNIEXPORT jint JNICALL Java_de_sssm_jt_raw_socket_JtRawSocket__1open
  (JNIEnv *, jobject){
  int recvfd = Socket(PF_INET,SOCK_RAW,ICMP);

  std::cerr << "opened raw icmp socket: " << recvfd << std::endl;

  return recvfd;
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtRawSocket__1close
  (JNIEnv *, jobject, jint fd){

  Close(fd);
  std::cerr << "closed raw icmp socket: " << fd << std::endl;
}

JNIEXPORT jobject JNICALL Java_de_sssm_jt_raw_socket_JtRawSocket__1recvfrom
  (JNIEnv *env, jobject, jint fd){
  struct sockaddr_in sa_from;
  socklen_t len;
  len = sizeof (sa_from);
  jbyte  msg[8192];

  int n = recvfrom(fd, &msg, sizeof(msg), 0, reinterpret_cast<struct sockaddr *> (&sa_from), &len);

  jbyteArray bytes = env->NewByteArray(n);
  env->SetByteArrayRegion(bytes,0,n,msg);

  jobject result = NULL;

  // turn from host to java string
  jstring host = env->NewStringUTF("unknown");
  char hostStr[128];
  if(NULL!=inet_ntop(AF_INET, &sa_from.sin_addr, hostStr, sizeof(hostStr))){
    host = env->NewStringUTF(hostStr);
  }

  jint port = -1;
  port = sa_from.sin_port;

  // get return object's class
  jclass cls = env->FindClass(JT_DATAGRAM_PACKET);
  if(NULL == cls){
    std::cerr << "could not load class " << JT_DATAGRAM_PACKET << std::endl;
    return result;
  }

  // get constructor
  jmethodID constructor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;I)V");
  if(NULL == constructor){
    std::cerr << "could not load constructor!" << std::endl;
    return result;
  }

  // create object
  result = env->NewObject(cls, constructor, bytes, host, port);

  return result;
}
