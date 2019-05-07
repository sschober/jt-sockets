# jt-sockets

A small native sockets library in the context of the jToMaTo framework.

# Architecture

Provides java APIs for datagram (UDP) and ICMP sockets, at the moment. The
intefaces are implemented natively in C++ to leverage raw socket capabilities.

# Notes

When you want to create raw sockets (`JtIcmpSocket`), adminstrative rights are
neccessary.

## Windows

Currently, I am trying to send UDP packets on one socket and receive TTL exceeded
messages on another (SOCK_RAW, and protocol ICMP or IPPROTO_IP). Theses efforts
fail. I am seeing the reply ICMP packets in wireshark, but they are not delivered
to my socket.

Howerver, when I send ICMP echo requests over a ICMP raw socket, I get the replies.
But, I explicitly want UDP tracing as well on windows.

Currently, I see the following options:

- there is an option (socket or ioctl), that allows to receive these ICMP packets.
- construct the UDP packets manually and send them over the raw socket.

### Update

I tried the IO_RCVALL ioctl option but failed. To make progress, I am pursuing to
implement ICMP trace route now and come back to the UDP option later.