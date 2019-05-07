#include <iostream>

#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtAbstractSocket.h"


JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1close
  (JNIEnv *, jobject, jint fd){

  Close(fd);
  std::cerr << "closed jt socket: " << fd << std::endl;
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1bind
  (JNIEnv *env, jobject, jint fd, jstring localAddress, jint port){
  std::cout << "binding socket..." << std::endl;
  sockaddr_in anyAddr;
  anyAddr.sin_family = AF_INET;
  const char *localAddrStr = env->GetStringUTFChars(localAddress, NULL);
  unsigned int addr = inet_addr(localAddrStr);
  anyAddr.sin_addr.s_addr = addr;
  anyAddr.sin_port = htons(0);
  int bindResult = bind(fd, (sockaddr*) &anyAddr, sizeof(anyAddr));
#ifdef __MINGW64__
  if( bindResult == SOCKET_ERROR ){
    std::cerr << "binding socket failed: " << WSAGetLastError() << std::endl;
    WSACleanup();
    exit(1);
  }
#endif
}
JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1init
  (JNIEnv *, jclass){
#ifdef __MINGW64__
  WSAData wsaData;
  if(WSAStartup(MAKEWORD(2,1), &wsaData) != 0){
    std::cerr << "failed to find winsock 2.1 or better" << std::endl;
    exit(1);
  }
  else{
    std::cout << "winsock 2.1 started up" << std::endl;
  }
#endif
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1setTtl
  (JNIEnv *, jobject, jint fd, jint ttl){
  SetSockOpt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof (int));
}