cmake_minimum_required (VERSION 3.12)
project (raw-socket)
add_library(native SHARED
  src/main/cpp/jt_socket_helper.cpp
  src/main/cpp/de_sssm_jt_raw_socket_jtabstractsocket.cpp
  src/main/cpp/de_sssm_jt_raw_socket_jticmpsocket.cpp
  src/main/cpp/de_sssm_jt_raw_socket_jtdatagramsocket.cpp)
include_directories("/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/target/classes)
set(CMAKE_CXX_COMPILER "g++")
