#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtDatagramSocket.h"

JNIEXPORT jint JNICALL Java_de_sssm_jt_raw_socket_JtDatagramSocket__1open
  (JNIEnv *, jobject){
  int recvfd = Socket(PF_INET,SOCK_DGRAM,0);

  std::cerr << "opened datagram socket: " << recvfd << std::endl;

  return recvfd;
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtDatagramSocket__1sendto
(JNIEnv *env, jobject, jint fd, jstring destHost, jint destPort, jbyteArray jbyteArray){

  struct sockaddr_in sa_dest;
  socklen_t sa_dest_len = sizeof (sa_dest);
  jbyte* bytes = env->GetByteArrayElements(jbyteArray, NULL);
  size_t bytesLen = env->GetArrayLength(jbyteArray);

  const char *destHostStr = env->GetStringUTFChars(destHost, NULL);

  sa_dest.sin_family = AF_INET;
  inet_pton(AF_INET,destHostStr, &sa_dest.sin_addr);
  sa_dest.sin_port = destPort;

  SendTo(fd, &bytes, bytesLen, 0, reinterpret_cast<struct sockaddr*>(&sa_dest), sa_dest_len);
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtDatagramSocket__1setTtl
(JNIEnv *, jobject, jint fd, jint ttl){
  SetSockOpt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof (int));
}
