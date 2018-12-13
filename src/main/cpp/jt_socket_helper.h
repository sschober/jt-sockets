#ifndef JT_SOCKET_HELPER_H
#define JT_SOCKET_HELPER_H

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int Socket(int family, int type, int protocol){
  int n;

  if((n=socket(family,type,protocol))<0){
    std::cerr << "socket error: " << strerror(errno) << std::endl;
    exit(1);
  }

  return n;
}

int Close(int fd){
  int n;

  if((n=close(fd))<0){
    std::cerr << "socket error: " << strerror(errno) << std::endl;
    exit(1);
  }

  return n;
}

#endif // JT_SOCKET_HELPER_H
