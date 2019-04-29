# jt-sockets

A small native sockets library in the context of the jToMaTo framework.

# Architecture

Provides java APIs for datagram (UDP) and ICMP sockets, at the moment. The 
intefaces are implemented natively in C++ to leverage raw socket capabilities.

# Notes

When you want to create raw sockets (`JtIcmpSocket`), adminstrative rights are
neccessary.