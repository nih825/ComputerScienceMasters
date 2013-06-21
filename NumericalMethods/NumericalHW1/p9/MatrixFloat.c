
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  float ** initializeArray(int size, float value){
    
    float ** matrix=(float **)malloc(sizeof(float *)*size);
    for(int i=0; i<size; i++)
      matrix[i]=(float *)malloc(sizeof(float)*size);
    for(int i=0; i<size; i++)
      for(int j=0;j<size;j++)
        matrix[i][j]=value;
    
    return matrix;
  }

  float ** multiplyMatrix(int size,float ** a, float ** b) {

    float value=1.5;
    float ** c=initializeArray(size,value);
    for(int i =0; i<size; i++)
      for(int j=0; j<size; j++)
        for(int k=0; k<size; k++)
	  c[i][j]+=a[i][k]*b[k][j];
     
    return c;
  }


  int main (void) {

    
    float normalizer=1.0/CLOCKS_PER_SEC;
    clock_t start,end;
    float ** a;
    float ** b;
    float ** c;
    int lengths[5]={100, 500, 1000, 1000, 1000};
    float timer[5]={0, 0, 0, 0, 0};
    float value=1.5;
    for(int i=0;i<5;i++){

     a=initializeArray(lengths[i],value);
     b=initializeArray(lengths[i],value);
     start=clock();
     c=multiplyMatrix(lengths[i],a,b);
     end=clock();
     free(a);
     free(b);
     free(c);
     timer[i]=(end-start)*normalizer;
     printf("%f\n",timer[i]);
   }
    

   return 0;
 }






