#include "mg.h"
#include "nrutil.h"
#include <stdio.h>
#include "Math.h"
#include <time.h>
int main(int argc, char **argv){
  int i,j;
  FILE *outfile;
  double **f;
  double **s;
  
  //Parameters
  int n=2049;
  int ncycle=3;
  double dt=.05;
  double alpha=.1;
  double c= alpha*dt;
  int sourceBool=0;  //1 indicates source heat to be used 0 indicates no source heat
  
  //Extra Parameters for CG
  int maxIter=10000;
  double tolerance=.00000001;  
  
  clock_t begin;
  clock_t end;
  f = dmatrix(1,n,1,n);
  s=dmatrix(1,n,1,n);
  double interval=1.0/n;
  //Initialize source to a constant for now
  double constantSource=0.1;
  int k, l;
  for(i=2; i<n; i++){
    for(j=2; j<n; j++)
      s[i][j]=constantSource;
  }


double basex, xcomponent, basey, ycomponent;
for(i=2; i<n; i++){
  for(j=2; j<n; j++){
    basex=interval*5*(i-1)-2.5;
    basex=pow(basex,2);
    basex=-basex;
    xcomponent=exp(basex);
        
    basey=interval*5*(j-1)-2.5;
    basey=pow(basey,2);
    basey=-basey;
    ycomponent=exp(basey);

    f[i][j]=xcomponent*ycomponent;
  }
}
 

  //Initialize multiplier for source (if source is set to false then sets sourceMult to 0
  //and thus source has no effect otherwise sets sourceMult to dt and then the source heat
  //gets multiplied by dt for the equations to work correctly)
  double sourceMult=0;
  if (sourceBool)
    sourceMult=dt;
/*
 //Code for Standard CG 
  begin = clock();
 cg(f,f, n, c, sourceMult, s, maxIter, tolerance); //Initial guess is guess of previous timestep
 end = clock();
 double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Time spent= %f", time_spent);
*/
//Code for Multigrid
/*
    begin = clock();
  mglin(f, n, ncycle, c, sourceMult, s);
  end = clock();
 double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Time spent= %f", time_spent);
*/
//Code for Preconditioned CG (Use mglin with 1 ncycle as guess)
  ncycle=1;
  double ** priorTimestep=dmatrix(1,n,1,n);
    for(l=2; l<n; l++){
      for(k=2; k<n; k++){
        priorTimestep[l][k]=f[l][k];
      }
    }
    begin = clock();
    mglin(f, n, ncycle, c, sourceMult, s);
    cg(priorTimestep,f, n, c, sourceMult, s, maxIter, tolerance);
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent= %f", time_spent);
  



}
