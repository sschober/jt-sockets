#include <iostream>

#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtIcmpSocket.h"

#define JT_DATAGRAM_PACKET "de/sssm/jt/raw/socket/JtDatagramPacket"
#define JT_RECEIVE_TIMEOUT_EXCEPTION "de/sssm/jt/raw/socket/JtReceiveTimeoutException"
#define ICMP 1

JNIEXPORT jint JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1open
  (JNIEnv *, jobject){
  int fd = Socket(PF_INET,SOCK_RAW,
#ifdef __MINGW64__
  IPPROTO_ICMP
#else
  ICMP
#endif
  );

  std::cout << "opened raw icmp socket: " << fd << std::endl;

  return fd;
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
  std::cout << "setting timeout on socket " << fd << " to " << seconds << " seconds and " << microSeconds << " microseconds" << std::endl;
#ifndef __MINGW64__
  struct timeval time_out;
  time_out.tv_sec = seconds;
  time_out.tv_usec = microSeconds;
  SetSockOpt(fd, SOL_SOCKET, SO_RCVTIMEO, &time_out, sizeof (time_out));
#else
  // windows wants no struct timeval
  seconds = 1000 * seconds + microSeconds;
  SetSockOpt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &seconds, sizeof(seconds));
#endif
}

struct ICMPHeader {
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
  unsigned short id;
  unsigned short seq;
  unsigned long timestamp;
};

#define ICMP_ECHO_REQUEST 8
unsigned short ip_checksum(unsigned short *buf, int size){
  unsigned long chksum = 0;
  while(size > 1){
    chksum += *buf++;
    size -= sizeof(unsigned short);
  }
  if(size){
    chksum += *(unsigned char*)buf;
  }
  chksum = (chksum >> 16) + (chksum & 0xffff);
  chksum += (chksum >> 16);
  return (unsigned short) (~chksum);
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtIcmpSocket__1ping
  (JNIEnv *env, jobject, jint fd, jstring destHost){
    char buf[8192];
    ICMPHeader *icmpHeader = (ICMPHeader*) &buf;
    icmpHeader->type = ICMP_ECHO_REQUEST;
    icmpHeader->code = 0;
    icmpHeader->id = (unsigned short) GetCurrentProcessId();
    icmpHeader->seq = 1;
    icmpHeader->checksum = 0;
    icmpHeader->timestamp = GetTickCount();
    icmpHeader->checksum = ip_checksum((unsigned short*)icmpHeader, sizeof(ICMPHeader));

    sockaddr_in dest;
    const char *destHostStr = env->GetStringUTFChars(destHost, NULL);
    unsigned int addr = inet_addr(destHostStr);
    dest.sin_addr.s_addr = addr;
    dest.sin_family = AF_INET;

    std::cout << "sending ping to " << destHostStr << std::endl;

    int bwrote = sendto(fd, buf, sizeof(ICMPHeader), 0, (sockaddr*)&dest, sizeof(dest));
    if( bwrote < 0){
      std::cerr << "failed to send ping: "
#ifdef __MINGW64__
      << WSAGetLastError()
#else
      << strerror(errno);
#endif
      << std::endl;
      exit(1);
    }
}