#include "SmoothFilter.h"
JNIEXPORT void JNICALL Java_SmoothFilter_csmooth
  (JNIEnv *env, jclass class, jint type, jintArray f, jdoubleArray filt)
{
	jboolean isCopy;
	int i, j, k;
	double sval;
	int channel;
	int* fp;
	double* filtp;
	jsize nx, nk;


	// find out how many channel each type has. 
	// 3 = TYPE_3BYTE_BGR 
	// 6 = TYPE_4BYTE_ABGR
	// 7 = TYPE_4BYTE_ABGR_PRE
	switch(type)
	{
	case 6:
	case 7:
		channel = 4;
		break;
	case 5:
		channel = 3;
		break;
	default:
		channel = 1;
		break;
	}

	printf("channel: %d\n", channel);

	nx = (*env)->GetArrayLength(env, f) / channel;
	nk = (*env)->GetArrayLength(env, filt);

	fp = (*env)->GetIntArrayElements(env, f, &isCopy);
	filtp = (*env)->GetDoubleArrayElements(env, filt, &isCopy);

	printf("is copy: %d\n", isCopy);

	for (i = 0; i < nx - nk; ++i){
	  for ( k = 0; k < channel; k++){
	    sval = 0.;
	    for (j = 0; j < nk; ++j){
	      sval += fp[(j+i)*channel+k]*filtp[j];
	    }
	    fp[i*channel+k] = (int)sval;
	  }
	}

	(*env)->ReleaseIntArrayElements(env, f, fp, 0);
	(*env)->ReleaseDoubleArrayElements(env, filt, filtp, 0);
	printf ("smooth done.\n");
}

