
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#include "jacobi_iteration.h"

//This calculates 1 iteration using the GaussSeidel method
vector<double> gaussSeidelIteration1step(vector<double> b, vector<double> prevIt, int nx, double dx, double alpha, double dt){
    double c=alpha*dt/(pow(dx,2));
    
    vector<double> xnextit;
    xnextit.resize(pow(nx,3));
    for(int i=1; i<nx+1; i++){
        for(int j=1; j<nx+1; j++) {
            for(int z=1; z<nx+1; z++){
                int loc=returnLocationJacobi(i,j,z,nx,nx,nx);
                int xlocright=returnLocationJacobi(i+1,j,z,nx,nx,nx);
                int xlocleft=returnLocationJacobi(i-1,j,z,nx,nx,nx);
                int ylocright=returnLocationJacobi(i,j+1,z,nx,nx,nx);
                int ylocleft=returnLocationJacobi(i,j-1,z,nx,nx,nx);
                int zlocright=returnLocationJacobi(i,j,z+1,nx,nx,nx);
                int zlocleft=returnLocationJacobi(i,j,z-1,nx,nx,nx);
                double newVal=0;
                if(i+1!=nx+1)
                    newVal+=prevIt[xlocright];
                if(i-1!=0)
                    newVal+=xnextit[xlocleft];
                if(j+1!=nx+1)
                    newVal+=prevIt[ylocright];
                if(j-1!=0)
                    newVal+=xnextit[ylocleft];
                if(z+1!=nx+1)
                    newVal+=prevIt[zlocright];
                if(z-1!=0)
                    newVal+=xnextit[zlocleft];
                
                newVal=c/(6*c+1)*newVal;
                newVal+=1/(6*c+1)*b[loc];
                xnextit[loc]=newVal;
            }
        }
    }
    
    return xnextit;
}

//This calculates 1 timestep using Gauss Seidel iteration
vector<double> gaussSeidelIteration(vector<double> b, int nx, double dx, double epsilon, double alpha, double dt, int maxIter){
    
    vector<double> initialGuess=b;
    vector<double> currentIt;
    currentIt=gaussSeidelIteration1step(b,b, nx,dx, alpha, dt);
    if(findDifference(currentIt,initialGuess, nx)<epsilon)
        return currentIt;
    vector<double> previousIt;
    for(int i=0; i<maxIter; i++){
        cout<<endl<<endl<<i<<endl<<endl;
        previousIt=currentIt;
        currentIt=gaussSeidelIteration1step(b,previousIt, nx,dx,alpha,dt);
        if(findDifference(currentIt,previousIt,nx)<epsilon)
            return currentIt;
    }
    
    cout<<"FAILURE TO CONVERGE"<<endl;
}



