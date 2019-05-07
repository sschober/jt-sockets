#ifndef JT_SOCKET_HELPER_H
#define JT_SOCKET_HELPER_H

#include <iostream>
#include <unistd.h>

#ifdef DARWIN
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif __MINGW64__
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

/**
 * Currently, all these functions try the underlying sockets API function,
 * log an error in case of failure and exit.
 *
 * TODO: rewrite error handling to throw java exceptions.
 */

/**
 * Creates a socket of given family, type and protocol.
 * Returns a handle to the socket on success, logs error and exits otherwise.
 */
int Socket(int family, int type, int protocol);

int Close(int fd);

ssize_t ReceiveFrom(int fd, void*, size_t, int, struct sockaddr *, socklen_t *);

ssize_t	SendTo(int, const void *, size_t, int, const struct sockaddr *, socklen_t);

int	SetSockOpt(int, int, int, const void *, socklen_t);

#endif // JT_SOCKET_HELPER_H
