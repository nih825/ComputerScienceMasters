#include "Utils.h"
double maxval(int, double*);

JNIEXPORT jdouble JNICALL Java_Utils_max
  (JNIEnv *env, jobject objc, jdouble f1, jdouble f2){

  if (f1 > f2)
    return(f1);
  else
    return(f2);
}

JNIEXPORT jdouble JNICALL Java_Utils_maxarr(JNIEnv *env, jobject obj, 
					    jdoubleArray arr){
  jsize length = (*env)->GetArrayLength(env,arr);
  jdouble* body = (*env)->GetDoubleArrayElements(env,arr,0);
  double* p2 = (double *) body;
  int nx = (int) length;
  double max = maxval(nx, body);
  return((jdouble) max);
}

double maxval(int len, double* arr){
  double max = arr[0];
  int i;
  for (i=0;i<len-1;i++)
    if (arr[i+1] > arr[i]) 
      max = arr[i+1];
  return(max);
}
