#include<stdio.h>
#include<ArrUtils.h>

static float maxval(float f1, float f2);
static float minval(float f1, float f2);

JNIEXPORT void JNICALL Java_ArrUtils_extrema
(JNIEnv *env, jclass class, jfloatArray arg1, jfloatArray arg2){
  int i;
  jfloat min, max;
  jsize length = (*env)->GetArrayLength(env, arg1);
  jfloat *arr  = (*env)->GetFloatArrayElements(env, arg1, 0);
  jfloat *ret  = (*env)->GetFloatArrayElements(env, arg2, 0);

  min = arr[0]; max = arr[0];

  for (i=1; i<length; ++i){
      max = maxval(max,arr[i]);
      min = minval(min,arr[i]);
  }

  ret[0] = min;
  ret[1] = max;

  /*  (*env)->SetFloatArrayRegion(env,arg2,0,0,&min);
      (*env)->SetFloatArrayRegion(env,arg2,1,1,&max);*/


  (*env)->ReleaseFloatArrayElements(env,arg1,arr,0);
  (*env)->ReleaseFloatArrayElements(env,arg2,ret,0);
}
  

static float maxval(float f1, float f2){
    if (f1 >= f2)
	return(f1);
    else
	return(f2);
}

static float minval(float f1, float f2){
    if (f1 <= f2)
	return(f1);
    else
	return(f2);
}
