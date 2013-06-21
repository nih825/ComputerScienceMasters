#include<stdio.h>
#include<Reader.h>

JNIEXPORT void JNICALL Java_Reader_read(JNIEnv *env, 
				      jobject obj, 
				      jbyteArray arr,
				      jstring file){
    FILE *fp;
    int i;
    int ret;
    jsize size = (*env)->GetArrayLength(env,arr);
    jbyte *body =(*env)->GetByteArrayElements(env,arr,0);
    const char *filename = (*env)->GetStringUTFChars(env, file, 0);

    fp = fopen(filename, "r");
    fread(body, sizeof(char), size, fp);

    fclose(fp);

    (*env)->ReleaseByteArrayElements(env, arr,body, 0);

    return;
}

