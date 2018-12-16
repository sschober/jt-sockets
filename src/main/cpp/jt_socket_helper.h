#ifndef JT_SOCKET_HELPER_H
#define JT_SOCKET_HELPER_H

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int Socket(int family, int type, int protocol);

int Close(int fd);

ssize_t ReceiveFrom(int fd, void*, size_t, int, struct sockaddr *, socklen_t *);

ssize_t	SendTo(int, const void *, size_t, int, const struct sockaddr *, socklen_t);

int	SetSockOpt(int, int, int, const void *, socklen_t);

#endif // JT_SOCKET_HELPER_H
