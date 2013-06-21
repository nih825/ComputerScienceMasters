
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//This method returns the row location based on the x,y,z coordinates for the matrix.
int returnLocationJacobi(int i, int j, int k, int nx, int ny, int nz){
    return (i-1)*ny*nz+(j-1)*nz+k-1; //subtracts 1 to convert to typical array based notation
}

//Solution is in the form of a 1d vector, this function maps it back into a 3d vector
vector<vector<vector<double>>> convertTo3dJacobi(vector<double> solution, int nx){
    vector<vector<vector<double> > > array;
  	array.resize(nx+2);
  	for (int i = 0; i < nx+2; i++) {
    	array[i].resize(nx+2);
    	for (int j = 0; j < nx+2; j++)
      		array[i][j].resize(nx+2);
  	}
    
    
    for(int i=0; i<nx+2; i++){
        for(int j=0; j<nx+2; j++){
            for(int k=0; k<nx+2; k++){
                if(i==0||i==nx+1||j==0||j==nx+1||k==0||k==nx+1){
                        array[i][j][k]=0;
                }
                else{
                    int location=returnLocationJacobi(i,j,k,nx,nx,nx);
                    array[i][j][k]=solution[location];
                }
                
            }
        }
    }
    
    
    return array;
    
}
//This creates the B vector by mapping the 3d vector of temperature data at the previous timestep to a 1d vector
vector<double> createBJacobi(vector<vector<vector<double>>> array,int nx){
    
    vector<double> b;
    b.resize(pow(nx,3));

    for(int i=1; i<nx+1; i++){
        for(int j=1; j<nx+1; j++){
            for(int z=1; z<nx+1; z++) {
                int location=returnLocationJacobi(i,j,z,nx,nx,nx);
                b[location]=array[i][j][z];
            }
        }
    }
    return b;
}
//This function calculates the new values for 1 iteration using the jacobi method
vector<double> jacobiIteration1step(vector<double> b, vector<double> prevIt, int nx, double dx, double alpha, double dt){
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
                    newVal+=prevIt[xlocleft];
                if(j+1!=nx+1)
                    newVal+=prevIt[ylocright];
                if(j-1!=0)
                    newVal+=prevIt[ylocleft];
                if(z+1!=nx+1)
                    newVal+=prevIt[zlocright];
                if(z-1!=0)
                    newVal+=prevIt[zlocleft];
                
                newVal=c/(6*c+1)*newVal;
                newVal+=1/(6*c+1)*b[loc];
                xnextit[loc]=newVal;
            }
        }
    }
    
    return xnextit;
}
//This function finds the difference between 2 iterations 
double findDifference(vector<double> a, vector<double> b, int nx){
    double sum=0;
    for(int i=0; i<nx*nx*nx; i++){
        sum+=pow(a[i]-b[i],2);
    }
    return sqrt(sum);
    
    
}
//This function is a loop that calculates 1 timestep by iterating until the difference in iteration is less than epsilon
vector<double> jacobiIteration(vector<double> b, int nx, double dx, double epsilon, double alpha, double dt, int maxIter){
    
    vector<double> initialGuess=b;
    vector<double> currentIt;
    currentIt=jacobiIteration1step(b,b, nx,dx, alpha, dt);
    if(findDifference(currentIt,initialGuess, nx)<epsilon)
        return currentIt;
    vector<double> previousIt;
    for(int i=0; i<maxIter; i++){
        cout<<endl<<endl<<i<<endl<<endl;
        previousIt=currentIt;
        currentIt=jacobiIteration1step(b,previousIt, nx,dx,alpha,dt);
        if(findDifference(currentIt,previousIt,nx)<epsilon)
            return currentIt;
    }
    
    cout<<"FAILURE TO CONVERGE"<<endl;
}



