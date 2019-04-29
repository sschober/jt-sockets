#ifndef JT_SOCKET_HELPER_H
#define JT_SOCKET_HELPER_H

#include <iostream>
#include <unistd.h>

#ifdef DARWIN
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif __MINGW64__
// TODO this only compiles on windows 10
#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

int Socket(int family, int type, int protocol);

int Close(int fd);

ssize_t ReceiveFrom(int fd, void*, size_t, int, struct sockaddr *, socklen_t *);

ssize_t	SendTo(int, const void *, size_t, int, const struct sockaddr *, socklen_t);

int	SetSockOpt(int, int, int, const void *, socklen_t);

#endif // JT_SOCKET_HELPER_H
