#include <stdio.h>
/*
  assumes f and fnew are of size (nx+2)*(ny+2)*(nz+2) and that the "boundaries" of f
  are set to zero. The boundaries are all values along the edge of the cube, e.g.
  f[:][0][0], f[:][ny+1][nz+1], etc. where : denotes "all elements"
*/
void j3d(float* f, float *fnew, int nx, int ny, int nz, int n_iter){
  int i,j,k;
  int iter; 
  void arrcpy(float *f, float *fnew, int nx, int ny, int nz);

  for (iter=0;iter<n_iter;++iter){
    for (i=1;i<=nx;++i)
      for (j=1;j<=ny;++j)
	for (k=1;k<=nz;++k)
	  fnew[i*ny*nz + j*nz + k]  = 1./6 *
	    (f[(i+1)*ny*nz + j*nz + k]  + 
	     f[(i-1)*ny*nz + j*nz + k]  + 
	     f[i*ny*nz + (j+1)*nz + k]  +
	     f[i*ny*nz + (j-1)*nz + k]  +
	     f[i*ny*nz + j*nz + (k+1)]  +
	     f[i*ny*nz + j*nz + (k-1)])  -
	    f[i*ny*nz + j*nz + k];
    arrcpy(f,fnew,nx,ny,nz);
    printf("%d\n", f[13]); // to have some sort of output to read from the stream in the bonus part
  }
  return;
}

void arrcpy(float *f, float *fnew, int nx, int ny, int nz){
  int i,j,k;
  for (i=1;i<=nx;++i)
    for (j=1;j<=ny;++j)
      for (k=1;k<=nz;++k)
	f[i*ny*nz + j*nz + k] = fnew[i*ny*nz + j*nz + k];
}

