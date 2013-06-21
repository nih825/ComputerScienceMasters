#include "HelloWorld.h"
JNIEXPORT void JNICALL Java_HelloWorld_displayHelloWorld(
			 JNIEnv *env, jobject obj){
  printf("Hello World\n");
}

  

