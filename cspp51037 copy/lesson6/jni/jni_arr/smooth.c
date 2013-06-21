#include "Smooth1dDriver.h"

JNIEXPORT void JNICALL Java_Smooth_csmooth___3D_3D
(JNIEnv *env, jclass class, jdoubleArray f, jdoubleArray filt){
  jboolean isCopy;
  int i, j;
  double sval;

  jsize nx = (*env)->GetArrayLength(env, f);
  jsize nk = (*env)->GetArrayLength(env, filt);
  
  double* fp = (*env)->GetDoubleArrayElements(env, f, &isCopy);
  double* filtp = (*env)->GetDoubleArrayElements(env, filt, &isCopy);

  printf("is copy: %d\n", isCopy);

  for (i = 0; i < nx - nk; ++i){
    sval = 0.;
    for (j = 0; j < nk; ++j){
      sval += fp[j+i]*filtp[j];
    }
    fp[i] = sval;
  }

  (*env)->ReleaseDoubleArrayElements(env, f, fp, 0);
  (*env)->ReleaseDoubleArrayElements(env, filt, filtp, 0);

}
