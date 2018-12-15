#include "jt_socket_helper.h"

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

ssize_t ReceiveFrom(int fd, void* msg, size_t msgLen, int, struct sockaddr *sa_from, socklen_t *sa_from_len){
  ssize_t n;

  if( (n= recvfrom(fd, msg, msgLen, 0, sa_from, sa_from_len)) < 0){
    std::cerr << "socket error: " << strerror(errno) << std::endl;
    exit(1);
  }

  return n;
}

ssize_t	SendTo(int fd, const void *bytes, size_t bytes_len,
               int flags, const struct sockaddr *sa_dest, socklen_t sa_dest_len){

  ssize_t n;
  if((n=sendto(fd, bytes, bytes_len, 0, sa_dest, sa_dest_len))<0){
    std::cerr << "socket error: " << strerror(errno) << std::endl;
  }

  return n;
}
