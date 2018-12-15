#include <iostream>

#include "jt_socket_helper.h"
#include "de_sssm_jt_raw_socket_JtAbstractSocket.h"

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1sayHello
  (JNIEnv *, jobject){
    std::cout << "jTomato native library" << std::endl;
}

JNIEXPORT void JNICALL Java_de_sssm_jt_raw_socket_JtAbstractSocket__1close
  (JNIEnv *, jobject, jint fd){

  Close(fd);
  std::cerr << "closed jt socket: " << fd << std::endl;
}
