//
//  main.cpp
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "cn.h"
#include "gaussian_elim.h"
#include "jacobi_iteration.h"

using namespace std;
//This method initializes a 3d temperature grid.  The inputs are the number of intervals for each of the 3 axis, the absolute sizes of the 3 axis, and the 6 boundary conditions, these 6 boundary conditions must be given even in the case of periodic just to initialize this grid however in the periodic case the boundarys set will have no effect on the answer so any values can be passed in if you plan on using the periodic solver, also the entries are set based on a gaussian distribution with small uniform random noise 
vector<vector<vector<double>>> initialize3d(int nx, int ny, int nz, double xsize, double ysize, double zsize,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6){
	vector<vector<vector<double> > > array;
  	array.resize(nx+2);
  	for (int i = 0; i < nx+2; i++) {
    	array[i].resize(ny+2);
    	for (int j = 0; j < ny+2; j++)
      		array[i][j].resize(nz+2);
  	}
    
	double intervalx=xsize/(nx+2);
	double intervaly=ysize/(ny+2);
	double intervalz=zsize/(nz+2);
    
	for(int i=0; i<nx+2; i++){
		for(int j=0; j<ny+2;j++){
			for(int k=0; k<nz+2; k++){
				double basex=5*(i+1)*intervalx-5*xsize/2;
				basex=pow(basex,2);
				basex=-basex;
				double xcomponent=exp(basex);
				
				double basey=5*(j+1)*intervaly-5*ysize/2;
				basey=pow(basey,2);
				basey=-basey;
				double ycomponent=exp(basey);
                
				double basez=5*(k+1)*intervalz-5*zsize/2;
				basez=pow(basez,2);
				basez=-basez;
				double zcomponent=exp(basez);
                
				array[i][j][k]=xcomponent*ycomponent*zcomponent+((double)(rand()%100))/2000.0;
				if(i==nx+1)
					array[i][j][k]=boundary1;
                else if (j==ny+1)
                    array[i][j][k]=boundary2;
                else if(k==nz+1)
                    array[i][j][k]=boundary3;
                else if(i==0)
                    array[i][j][k]=boundary4;
                else if(j==0)
                    array[i][j][k]=boundary5;
                else if(k==0)
                    array[i][j][k]=boundary6;
            }
            
		}
        
	}
    return array;
}
//This solves the temperature for the next timestep based on the previous timestep, inputs are the 3d vector of the previous temperatures, the diffusivity constant alpha, the size of the x y and z intervals, the total number of x y and z intervals, the change in the time interval dt, a boolean (wraparound) if set to true uses periodic boundary counditions rather than the constant boundary conditions that are set, a boolean (sourceBool) if true adds in a source heat based on the next argument passed the source 3d vector which is the heat input at each location, this must be passed even if sourceBool is false however it will have no effect thus any arbitrary 3dvector can be passed for the source if sourceBool is set to false 
vector<vector<vector<double>>> FTCS(vector<vector<vector<double>>> previous, double alpha, double dx, double dy, double dz, double dt, int nx, int ny, int nz, bool wraparound,bool sourceBool, vector<vector<vector<double>>> source){
    
    double c1= alpha*dt/pow(dx,2);
    double c2= alpha*dt/pow(dy,2);
    double c3= alpha*dt/pow(dz,2);
    vector<vector<vector<double>>> nextStep=previous;
    double sourceMult=dt;
    if(!sourceBool)
        sourceMult=0;
    
    if(!wraparound){
        for(int i=1; i<nx+1; i++){
            for(int j=1; j<ny+1; j++){
                for(int k=1; k<nz+1; k++){
                    double previousVal=previous[i][j][k];
                    double xchange=c1*(previous[i+1][j][k]+previous[i-1][j][k]-2*previous[i][j][k]);
                    double ychange=c2*(previous[i][j+1][k]+previous[i][j-1][k]-2*previous[i][j][k]);
                    double zchange=c3*(previous[i][j][k+1]+previous[i][j][k-1]-2*previous[i][j][k]);
                    nextStep[i][j][k]=previousVal+xchange+ychange+zchange+sourceMult*source[i][j][k];
                }
            }
        }
    }
    else{
        for(int i=1; i<nx+1; i++){
            for(int j=1; j<ny+1; j++){
                for(int k=1; k<nz+1; k++){
                    double previousVal=previous[i][j][k];
                    double xchange=c1*(previous[i+1][j][k]+previous[i-1][j][k]-2*previous[i][j][k]);
                    if(i+1==nx+1)
                        xchange=c1*(previous[1][j][k]+previous[i-1][j][k]-2*previous[i][j][k]);
                    else if(i-1==0)
                        xchange=c1*(previous[i+1][j][k]+previous[nx][j][k]-2*previous[i][j][k]);
                    double ychange=c2*(previous[i][j+1][k]+previous[i][j-1][k]-2*previous[i][j][k]);
                    if(j+1==ny+1)
                        ychange=c2*(previous[i][1][k]+previous[i][j-1][k]-2*previous[i][j][k]);
                    else if(j-1==0)
                        ychange=c2*(previous[i][j+1][k]+previous[i][ny][k]-2*previous[i][j][k]);
                    double zchange=c3*(previous[i][j][k+1]+previous[i][j][k-1]-2*previous[i][j][k]);
                    if(k+1==nz+1)
                        zchange=c3*(previous[i][j][1]+previous[i][j][k-1]-2*previous[i][j][k]);
                    else if(k-1==0)
                        zchange=c3*(previous[i][j][k+1]+previous[i][j][nz]-2*previous[i][j][k]);
                    nextStep[i][j][k]=previousVal+xchange+ychange+zchange+sourceMult*source[i][j][k];
                }
            }
        }
    }
    return nextStep;
}

void printSlice(vector<vector<vector<double>>> array, int i, int ny, int nz){
    for(int j=0; j<ny+2; j++){
        cout<<endl;
        for(int k=0; k<nz+2; k++)
            cout<<array[i][j][k]<<" ";
    }
}
//This method initializes a source heat vector based on a constant temp, the number of x y and z intervals.  You do not have to used this method, you can create any sources 3d vector and pass it in to the FCTS solver this is just one easy way of creating a constant source across location
vector<vector<vector<double>>> initializeSourceVec(double sourcenum, int nx, int ny, int nz){
    vector<vector<vector<double>>> sourceVec;
    sourceVec.resize(nx+2);
  	for (int i = 0; i < nx+2; i++) {
    	sourceVec[i].resize(ny+2);
    	for (int j = 0; j < ny+2; j++)
      		sourceVec[i][j].resize(nz+2);
  	}
    for(int i=0; i<nx+2; i++){
        for(int j=0; j<ny+2; j++){
            for(int k=0; k<nz+2; k++){
                sourceVec[i][j][k]=sourcenum;
                if(i==0||j==0||k==0||i==nx+1||j==ny+1||k==nz+1)
                    sourceVec[i][j][k]=0;
            }
        }
    }
    return sourceVec;
}


int main1(void){
    int nx=8;
    int ny=8;
    int nz=8;
    double xsize=1;
    double ysize=1;
    double zsize=1;
    double alpha=.001;
    double dt=.0005;
    double boundary1=0;
    double boundary2=0;
    double boundary3=0;
    double boundary4=0;
    double boundary5=0;
    double boundary6=0;
    bool wrapAround=false;
    bool source=false;
    int numIterations=1000000;
    int maxIterationsPerTimestep=1000;
    double epsilon=.0000001;
    clock_t t0=clock();

    vector<vector<vector<double>>> sourceVec=initializeSourceVec(0.1,nx,ny,nz);
    vector<vector<vector<double>>> array= initialize3d(nx,ny,nz,xsize,ysize,zsize,boundary1,boundary2, boundary3, boundary4, boundary5, boundary6);
    
    double dx=xsize/(nx+2);
    double dy=ysize/(ny+2);
    double dz=zsize/(nz+2);
    
    printSlice(array,4,ny,nz);
    vector<double> b= createBJacobi(array,nx);
    vector<double>sol=jacobiIteration(b,nx,dx,epsilon,alpha,dt, maxIterationsPerTimestep);
    vector<vector<vector<double>>> sol3d=convertTo3dJacobi(sol, nx);
   printSlice(sol3d,4,ny,nz);
    
    for(int i=0; i<numIterations; i++){
        b=createBJacobi(sol3d,nx);
        sol=jacobiIteration(b,nx,dx,epsilon,alpha,dt, maxIterationsPerTimestep);
        sol3d=convertTo3dJacobi(sol, nx);
        
    }
    printSlice(sol3d,4,ny,nz);
    //printSlice(array,4,ny,nz);
        
/*    vector<vector<vector<double>>> array1=FTCS(array,alpha,dx,dy,dz,dt,nx,ny,nz, wrapAround, source, sourceVec);
    //printSlice(array1,4,ny,nz);
    for(int i=0; i<numIterations-1; i++){
        array1=FTCS(array1,alpha,dx,dy,dz,dt,nx,ny,nz,wrapAround,source,sourceVec);
       // printSlice(array1,4,ny,nz);
    }
*/
    

    
    
/*    vector<vector<double>> a=createA(nx, ny, nz, alpha, dt, dx, dy, dz,wrapAround,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
    vector<double> b=createB(array,nx, ny, nz, alpha, dt, dx, dy, dz, source, sourceVec,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
    vector<double> solution=gaussian_elim(a, b);
    vector<vector<vector<double>>> solution3d=convertTo3d(solution, nx, ny, nz,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
//    printSlice(solution3d,4,ny,nz);
    
    for(int i=0; i<numIterations-1; i++){
        a= createA(nx, ny, nz, alpha, dt, dx, dy, dz,wrapAround,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
        b=createB(solution3d,nx, ny, nz, alpha, dt, dx, dy, dz,source,sourceVec,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
        solution=gaussian_elim(a, b);
        solution3d=convertTo3d(solution, nx, ny, nz,boundary1, boundary2, boundary3, boundary4,boundary5, boundary6);
     //   printSlice(solution3d,4,ny,nz);
    }*/
    
    clock_t t1=clock()-t0;
    double elapsed=double(t1-t0)/(CLOCKS_PER_SEC);
    cout<<endl<<endl<<"Time Elapsed: "<<elapsed;
    return 0;
    
}

