#include "nrutil.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void mprint(double **matrix, int m, char *label);
void upper_triangulate(double **A, double *b, int m);
void vprint(double *vector, int m, char *label);
void back_sub(double **A, double *x, double *b, int m);

int main(int argc, char **argv)
{
  double **A, *b, *x;
  int n = 3;
  A = dmatrix(1,n,1,n);
  b = dvector(1,n);
  x = dvector(1,n);
  A[1][1] = 1; A[1][2]= 1; A[1][3] = 2;
  A[2][1] = 2; A[2][2]= 4; A[2][3] = -3;
  A[3][1] = 3; A[3][2]= 6; A[3][3] = -5;

  b[1] = 9; b[2] = 1; b[3] = 0;
  mprint(A,n,"A original");
  vprint(b,n,"b original");

  upper_triangulate(A,b,n);
  back_sub(A,x,b,n);
  mprint(A,n,"A");
  vprint(b,n,"b");
  vprint(x,n,"x");
}

void mprint(double **matrix, int m, char *label)
{
  int i, j,k;
  printf("%s:\n",label);

  for (i = 1; i <= m; ++i){
    for (j = 1; j <= m; ++j){
      printf("%10.2f ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n------------------------\n");
}

void vprint(double *vector, int m, char *label)
{
  int i, j;
  printf("%s:\n",label);

  for (i = 1; i <= m; ++i){
    printf("%10.2f ", vector[i]);
  }

  printf("\n------------------------\n");
}

void upper_triangulate(double **A, double *b, int m)
{
  int i,j,k;

  double scale;
  for (j=1;j<m;++j){           /* loop over columns */
    for (i=j+1;i<=m;++i){      /* loop over rows beneath pivot */
      if (A[i][j] != 0){       /* if entry not zero already */
	scale = A[i][j]/A[j][j];  /* zero out based on pivot */
	for (k=1;k<=m;++k){
	  A[i][k] = A[i][k] - A[j][k]*scale;
	}
	b[i] = b[i] - b[j]*scale; /* same for b */
      }
    }
  }
}

void back_sub(double **A, double *x, double *b, int m)
{
  int i,j;
  x[m] = b[m]/A[m][m];

  for (i=m-1;i>=1;--i){
    x[i] = b[i];
    for (j=i+1;j<=m;++j){
      x[i] -= A[i][j]*x[j];
    }
    x[i]/=A[i][i];
  }
}
