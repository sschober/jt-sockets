#include <iostream>

#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtIcmpSocket.h"

#define JT_DATAGRAM_PACKET "de/sssm/jt/raw/socket/JtDatagramPacket"
#define JT_RECEIVE_TIMEOUT_EXCEPTION "de/sssm/jt/raw/socket/JtReceiveTimeoutException"
#define ICMP 1

JNIEXPORT jint JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1open
  (JNIEnv *, jobject){
  int recvfd = Socket(PF_INET,SOCK_RAW,ICMP);

  std::cerr << "opened raw icmp socket: " << recvfd << std::endl;

  return recvfd;
}


JNIEXPORT jobject JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1recvfrom
  (JNIEnv *env, jobject, jint fd){

  struct sockaddr_in sa_from;
  socklen_t len = sizeof (sa_from);
  jbyte msg[8192];

  ssize_t n = ReceiveFrom(fd, &msg, sizeof(msg), 0, reinterpret_cast<struct sockaddr *> (&sa_from), &len);

  jobject result = NULL;

  if( 0 > n && EWOULDBLOCK == errno ){
    // time-out occured
    jclass exception = env->FindClass(JT_RECEIVE_TIMEOUT_EXCEPTION);
    if(NULL == exception){
      std::cerr << "could not find exception: " << JT_RECEIVE_TIMEOUT_EXCEPTION << std::endl;
      exit(1);
    }
    else{
      std::cout << "throwing exception: " << JT_RECEIVE_TIMEOUT_EXCEPTION << std::endl;
    }
    env->ThrowNew(exception, "receive timeout occurred");
    return result;
  }

  // copy bytes from native array to java based array
  jbyteArray bytes = env->NewByteArray( static_cast<int>(n));
  env->SetByteArrayRegion(bytes,0,static_cast<int>(n),msg);

  // turn from host to java string
  jstring sourceHost = env->NewStringUTF("unknown");
  char hostStr[128];
  if(NULL!=inet_ntop(AF_INET, &sa_from.sin_addr, hostStr, sizeof(hostStr))){
    sourceHost = env->NewStringUTF(hostStr);
  }
  jint sourcePort = sa_from.sin_port;

  // not interessting in this context
  jstring destHost = env->NewStringUTF("unknown");
  jint destPort = -1;

  // get return object's class
  jclass cls = env->FindClass(JT_DATAGRAM_PACKET);
  if(NULL == cls){
    std::cerr << "could not load class " << JT_DATAGRAM_PACKET << std::endl;
    return result;
  }

  // get constructor
  jmethodID constructor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;ILjava/lang/String;I)V");
  if(NULL == constructor){
    std::cerr << "could not load constructor!" << std::endl;
    return result;
  }

  // create object
  result = env->NewObject(cls, constructor, bytes, sourceHost, sourcePort, destHost, destPort);

  return result;
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1setTimeOut
(JNIEnv *, jobject, jint fd, jint seconds, jint microSeconds){
  struct timeval time_out;
  time_out.tv_sec = seconds;
  time_out.tv_usec = microSeconds;
  SetSockOpt(fd, SOL_SOCKET, SO_RCVTIMEO, &time_out, sizeof (time_out));
}
