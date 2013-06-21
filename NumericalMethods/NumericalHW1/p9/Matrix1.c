
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  int ** initializeArray(int size, int value){
    
    int ** matrix=(int **)malloc(sizeof(int *)*size);
    for(int i=0; i<size; i++)
      matrix[i]=(int *)malloc(sizeof(int)*size);
    for(int i=0; i<size; i++)
      for(int j=0;j<size;j++)
        matrix[i][j]=value;
    
    return matrix;
  }

  int ** multiplyMatrix(int size,int ** a, int ** b) {

    int ** c=initializeArray(size,1);
    for(int i =0; i<size; i++)
      for(int j=0; j<size; j++)
        for(int k=0; k<size; k++)
	  c[i][j]+=a[i][k]*b[k][j];
     
    return c;
  }


  int main (void) {

    
    float normalizer=1.0/CLOCKS_PER_SEC;
    clock_t start,end;
    int ** a;
    int ** b;
    int ** c;
    int lengths[5]={100, 250, 500, 750, 1000};
    float timer[5]={0, 0, 0, 0, 0};

    for(int i=0;i<5;i++){

     a=initializeArray(lengths[i],1);
     b=initializeArray(lengths[i],1);
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






