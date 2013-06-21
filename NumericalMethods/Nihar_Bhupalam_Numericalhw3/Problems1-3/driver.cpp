
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "cn.h"
#include "gaussian_elim.h"
#include "jacobi_iteration.h"
#include "ftcs.h"
#include "GaussSeidel.h"
#include "successive_over_relaxation.h"
int main(void){
    int nx=100;
    double size=1;
    double alpha=.1;
    double dt=.05;
    int numIterations=100000;
    int maxIterationsPerTimestep=10000;
    double epsilon=.0000001;
    double w=1.5;
    
    vector<vector<vector<double>>> sourceVec=initializeSourceVec(0.1,nx,nx,nx);
    vector<vector<vector<double>>> array= initialize3d(nx,nx,nx,size,size,size,0,0,0, 0, 0,0);
    vector<double> w1={.7,.8,.9,1,1.1,1.2,1.3,1.4};
    vector<double> time;
    time.resize(w1.size());
    double dx=size/(nx+2);
    
    
    
    /* 
     //Code for Jacobi iteration
     clock_t t0;
     clock_t t1;
     double elapsed;
     
     vector<double> b= createBJacobi(array,nx);
     t0=clock();
     vector<double>sol=jacobiIteration(b,nx,dx,epsilon,alpha,dt, maxIterationsPerTimestep);
     t1=clock()-t0;
     elapsed=double(t1-t0)/(CLOCKS_PER_SEC);
     cout<<endl<<endl<<"Time Elapsed: "<<elapsed<<endl;
    */
    //Code for SOR Iteration
    clock_t t0;
    clock_t t1;
    double elapsed;
    
    //printSlice(array,4,nx,nx);
    vector<double> b= createBJacobi(array,nx);
    t0=clock();
    vector<double>sol=sorIteration(b,nx,dx,epsilon,alpha,dt, maxIterationsPerTimestep,w);
    t1=clock()-t0;
    elapsed=double(t1-t0)/(CLOCKS_PER_SEC);
    cout<<endl<<endl<<"Time Elapsed: "<<elapsed<<"w: "<<w;
    
    //Code for GaussSeidelIteration
    /* clock_t t0;
     clock_t t1;
     double elapsed;
    vector<double> b= createBJacobi(array,nx);
    t0=clock();
    vector<double>sol=gaussSeidelIteration(b,nx,dx,epsilon,alpha,dt, maxIterationsPerTimestep);
    
     t1=clock()-t0;
     elapsed=double(t1-t0)/(CLOCKS_PER_SEC);
    cout<<endl<<endl<<"Time Elapsed: "<<elapsed<<endl;
    
    */
    
    
    return 0;
    
}