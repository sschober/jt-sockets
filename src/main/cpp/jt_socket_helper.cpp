#include "jt_socket_helper.h"

/*
 * winsock2 takes char * arguments, where standard posix takes void *.
 * So we define a cast on windows, and nothing on other platforms.
 */
#ifdef __MINGW64__
#define MW64_TO_CHAR_P (char *)
#else
#define MW64_TO_CHAR_P
#endif

int Socket(int family, int type, int protocol){
  int n;
#ifndef __MINGW64__
  if((n=socket(family,type,protocol))<0){
    std::cerr << "socket error: Socket: " << strerror(errno) << std::endl;
    exit(1);
  }
#else
  n = WSASocket(family,type,protocol,0,0,0);
  if( (SOCKET) n == INVALID_SOCKET || n < 0 ){
    std::cerr << "failed to create socket: " << WSAGetLastError() << std::endl;
    exit(1);
  }
#endif
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
  std::cerr << "receiving from socket " << fd << " msgLen=" << msgLen << " sa_from_len=" << *sa_from_len << std::endl;
  if( (n = recvfrom(fd, MW64_TO_CHAR_P msg, msgLen, 0, sa_from, sa_from_len)) < 0){
#ifndef __MINGW64__
    if(EWOULDBLOCK == errno){
#else
    int lastError = WSAGetLastError();
    if(lastError == WSAETIMEDOUT){
#endif
      std::cerr << "time out on socket: " << fd << std::endl;
    }
    else{
      std::cerr << "socket error: ReceiveFrom: "
#ifndef __MINGW64__
      << strerror(errno)
#else
      ;
      LPVOID lpMsgBuf;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
      fprintf(stderr, "%s", (char*) lpMsgBuf);
#endif
      //<< std::endl;
      exit(1);
    }
  }
  std::cout << "read " << n << " bytes" << std::endl;
  return n;
}

ssize_t	SendTo(int fd, const void *bytes, size_t bytes_len,
               int flags, const struct sockaddr *sa_dest, socklen_t sa_dest_len){

  ssize_t n;
  // std::cerr << "sending " << bytes_len << " bytes to " << inet_ntoa( ((sockaddr_in*) sa_dest)->sin_addr ) << std::endl;
  if((n=sendto(fd, MW64_TO_CHAR_P bytes, bytes_len, 0, sa_dest, sa_dest_len)) < 0 ){
    std::cerr << "socket error: SendTo: " << strerror(errno) << std::endl;
  }

  return n;
}

int	SetSockOpt(int fd, int level, int optname, const void *opt, socklen_t optlen){

  int n;
  if( ( n = setsockopt(fd, level, optname, MW64_TO_CHAR_P opt, optlen ))){
    std::cerr << "socket error: SetSockOpt: "
#ifndef __MINGW64__
    << strerror(errno)
#else
    << WSAGetLastError()
#endif
    << std::endl;
  }

  return n;
}
