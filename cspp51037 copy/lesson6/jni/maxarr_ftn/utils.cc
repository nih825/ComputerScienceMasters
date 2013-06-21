#include "Utils.h"
void maxval_(int*, double*, double*);

JNIEXPORT jdouble JNICALL Java_Utils_max (JNIEnv * env, jobject obj, 
					  jdouble f1, jdouble f2){
  if (f1 > f2)
    return(f1);
  else
    return(f2);
}

JNIEXPORT jdouble JNICALL Java_Utils_maxarr(JNIEnv *env, jobject obj, 
					    jdoubleArray arr){
  jsize length = (*env)->GetArrayLength(env,arr);
  jdouble* body =(*env)->GetDoubleArrayElements(env,arr,0);
  double* p2 = (double *) body;
  int nx = (int) length;
  double max;
  maxval_(&nx, p2, &max);
  return((jdouble) max);
}

