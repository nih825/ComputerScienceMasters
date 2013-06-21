#include "mg.h"
#include "nrutil.h"
#include <stdio.h>
void init_src(double **f, int n);

int main(int argc, char **argv){
  int i,j;
  FILE *outfile;
  double **f;
  int n=1025;
  int ncycle=1;
  f = dmatrix(1,n,1,n);
  init_src(f,n);
  outfile = fopen("rhs.dat", "w");
  fwrite(&f[1][1],sizeof(double),n*n,outfile);
  fclose(outfile);

  mglin(f,n,ncycle);
  outfile = fopen("soln.dat", "w");
  fwrite(&f[1][1],sizeof(double),n*n,outfile);
  fclose(outfile);
}

void init_src(double **f, int n){
  int mid;
  int i,j;
  int lwr,uppr;
  
  mid = n/2;
  //  lwr = mid - 10;
  //  uppr = mid + 10;
  //  printf("lower, upper: %d %d\n", lwr, uppr);
  //  f[mid][mid] = 100.;

  for (i=1;i<=n;++i)
    for (j=1;j<=n;++j)
      f[i][j] = 100.;

      return 0;
    }

}
