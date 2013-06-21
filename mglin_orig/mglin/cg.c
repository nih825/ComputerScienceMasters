#include "mg.h"
#include "nrutil.h"
#include<stdio.h>
#include "math.h"


void cg(double **b, double **x, int n, double c, double sourceMult, double **s, int maxIter, double tolerance){
	double dx=1/(double)n;
	c=c/(dx*dx);
	
	double rsold=0;
	//First calculate residual
	double ** resid=dmatrix(1,n,1,n);
	double **p=dmatrix(1,n,1,n);
	int j, i;
	for (i=2;i<n;i++) {
    	for (j=2;j<n;j++){
      		resid[i][j] = c*(x[i+1][j]+x[i-1][j]+x[i][j+1]+x[i][j-1]) -
			(1+4.0*c)*x[i][j] + b[i][j]+s[i][j]*sourceMult;
			rsold+=resid[i][j]*resid[i][j];
   			p[i][j]=resid[i][j];
   		}
   	}
  /* Boundary points.*/
  for (i=1;i<=n;i++) {
    resid[i][1]=resid[i][n]=resid[1][i]=resid[n][i]=0.0;
    p[i][1]=p[i][n]=p[1][i]=p[n][i]=0.0;
   }
   int iter=0;
   double alpha;
   double **ap=dmatrix(1,n,1,n);
   while(iter<maxIter){
   		for(i=2; i<n; i++){
   			for(j=2; j<n; j++){
   				ap[i][j]=(1+4*c)*p[i][j]-c*p[i-1][j]-c*p[i+1][j]-c*p[i][j+1]-c*p[i][j-1];

   			}
   		}



   		iter+=1;
   		alpha=0;
   		for(i=2; i<n; i++){
   			for(j=2; j<n; j++){
   				alpha+=p[i][j]*(ap[i][j]);
   			}
   		}
   		alpha=rsold/alpha;
   		
   		double rsnew=0;
   		for(i=2; i<n; i++){
   			for(j=2; j<n; j++){
   				x[i][j]=x[i][j]+alpha*p[i][j];
   				resid[i][j]=resid[i][j]-alpha*ap[i][j];
   				rsnew+=resid[i][j]*resid[i][j];
   			}
   		}

   		if(sqrt(rsnew)<tolerance)
   			break;
   		
        
        for(i=2; i<n; i++){
   			for(j=2; j<n; j++){
   				p[i][j]=resid[i][j]+rsnew/rsold*p[i][j];
   			}
   		}
   		rsold=rsnew;

   }

	
   printf("Iterations: %d \n \n", iter);




}