
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//This method returns the row location based on the x,y,z coordinates for the matrix.
int returnLocation(int i, int j, int k, int nx, int ny, int nz){
    return (i-1)*ny*nz+(j-1)*nz+k-1+6;
}

//Once I have a solution using cran-nicholson it is in the form of a 1d vector, this function maps it back into a 3d vector
vector<vector<vector<double>>> convertTo3d(vector<double> solution, int nx, int ny, int nz, double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6){
   /* int currenti=0;
    int currentj=0;
    int currentz=0;*/
    vector<vector<vector<double> > > array;
  	array.resize(nx+2);
  	for (int i = 0; i < nx+2; i++) {
    	array[i].resize(ny+2);
    	for (int j = 0; j < ny+2; j++)
      		array[i][j].resize(nz+2);
  	}

    
    for(int i=0; i<nx+2; i++){
        for(int j=0; j<ny+2; j++){
            for(int k=0; k<nz+2; k++){
                if(i==0||i==nx+1||j==0||j==ny+1||k==0||k==nz+1){
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
                else{
                    int location=returnLocation(i,j,k,nx,ny,nz);
                    array[i][j][k]=solution[location];
                }
                
            }
        }
    }
    
    
    /*for(int i=0; i<nx*ny*nz; i++){
        if(currenti==0||currenti==nx+1||currentj==0||currentj==ny+1||currentz==0||currentz==nz+1)
            array[currenti][currentj][currentz]=0;
        else
            array[currenti][currentj][currentz]=solution[i];
        currentz++;
        if(currentz>=nz){
            nz=0;
            currentj++;
            if(currentj>=ny){
                currentj=0;
                currenti++;
            }
        }
    }*/
    return array;
    
}
// This creates the B vector, the inputs are the 3d vector of temperatures at the previous timestep, the number of x y and z intervals, the diffusivity constant alpha, the length of the timestep dt, the size of the x y and z intervals, a source bool if there is a source of heat along with a 3d source vector if there is a source of heat (this must be passed in even if source bool is false but it will not be used if that is the case), and the 6 boundary conditions.  It sets up a b vector with the first 6 rows the 6 boundary conditions (these will have no effect if when generating the a matrix the wrapAround bool is set to true)
vector<double> createB(vector<vector<vector<double>>> array,int nx, int ny, int nz, double alpha, double dt, double dx, double dy, double dz, bool source, vector<vector<vector<double>>> sourceVec,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6){
    
    vector<double> b;
    b.resize(nx*ny*nz+6);
    
    double c1=alpha*dt/(2*pow(dx,2));
    double c2=alpha*dt/(2*pow(dy,2));
    double c3=alpha*dt/(2*pow(dz,2));
    double sourceMult=0;
    if(source)
        sourceMult=dt;
    
    b[0]=boundary1;
    b[1]=boundary2;
    b[2]=boundary3;
    b[3]=boundary4;
    b[4]=boundary5;
    b[5]=boundary6;
    
    for(int i=1; i<nx+1; i++){
        for(int j=1; j<ny+1; j++){
            for(int z=1; z<nz+1; z++) {
                int location=returnLocation(i,j,z,nx,ny,nz);
                b[location]=array[i][j][z]+c1*(array[i+1][j][z]+array[i-1][j][z]-2*array[i][j][z])+c2*(array[i][j+1][z]+array[i][j-1][z]-2*array[i][j][z])+c3*(array[i][j][z+1]+array[i][j][z-1]-2*array[i][j][z])+sourceMult*sourceVec[i][j][z];
            }
        }
    }
    return b;
}
//This method creates the A matrix, the inputs are the size of the x y and z axis, the diffusivity constant alpha, the time interval dt, the size of the x y and z intervals, a wrapAround bool which if true will utilize the neighbor on the opposite side instead of the constant boundary conditions, and finally the 6 boundary conditions which must be passed in even if wrapAround is true they just will not be used if wrapAround is true
vector<vector<double>> createA(int nx, int ny, int nz, double alpha, double dt, double dx, double dy, double dz,bool wraparound,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6){
    
    vector<vector<double>> a;
    a.resize(nx*ny*nz+6);
    for(int i=0; i<nx*ny*nz+6;i++)
        a[i].resize(nx*ny*nz+6);
    
    
    for(int i=0; i<nx*ny*nz+6; i++) {
        for(int j=0; j<nx*ny*nz+6;j++)
            a[i][j]=0;
    }
    a[0][0]=1;
    a[1][1]=1;
    a[2][2]=1;
    a[3][3]=1;
    a[4][4]=1;
    a[5][5]=1;
    
    double c1=alpha*dt/(2*pow(dx,2));
    double c2=alpha*dt/(2*pow(dy,2));
    double c3=alpha*dt/(2*pow(dz,2));
    if(!wraparound){
        for(int i=1; i<nx+1; i++){
            for(int j=1; j<ny+1; j++){
                for(int z=1; z<nz+1; z++) {
                    int location=returnLocation(i,j,z,nx,ny,nz);
                    a[location][location]=1+2*c1+2*c2+2*c3;
                    int xlocright=returnLocation(i+1,j,z,nx,ny,nz);
                    int xlocleft=returnLocation(i-1,j,z,nx,ny,nz);
                    int ylocright=returnLocation(i,j+1,z,nx,ny,nz);
                    int ylocleft=returnLocation(i,j-1,z,nx,ny,nz);
                    int zlocright=returnLocation(i,j,z+1,nx,ny,nz);
                    int zlocleft=returnLocation(i,j,z-1,nx,ny,nz);
                    
                    if(i+1==nx+1)
                        a[location][0]=-c1;
                    else
                        a[location][xlocright]=-c1;

                    if(i-1==0)
                        a[location][3]=-c1;
                    else
                        a[location][xlocleft]=-c1;
                    if(j+1==ny+1)
                        a[location][1]=-c2;
                    else
                        a[location][ylocright]=-c2;
                    if(j-1==0)
                        a[location][4]=-c2;
                    else
                        a[location][ylocleft]=-c2;
                    if(z+1==nz+1)
                        a[location][2]=-c3;
                    else
                        a[location][zlocright]=-c3;
                    if(z-1==0)
                        a[location][5]=-c3;
                    else
                        a[location][zlocleft]=-c3;
                    
                }
            }
        }
    }
    else{
        for(int i=1; i<nx+1; i++){
            for(int j=1; j<ny+1; j++){
                for(int z=1; z<nz+1; z++) {
                    int location=returnLocation(i,j,z,nx,ny,nz);
                    a[location][location]=1+2*c1+2*c2+2*c3;
                    int xlocright=returnLocation(i+1,j,z,nx,ny,nz);
                    if(i+1==nx+1)
                        xlocright=returnLocation(1,j,z,nx,ny,nz);
                    int xlocleft=returnLocation(i-1,j,z,nx,ny,nz);
                    if(i-1==0)
                        xlocleft=returnLocation(nx,j,z,nx,ny,nz);
                    int ylocright=returnLocation(i,j+1,z,nx,ny,nz);
                    if(j+1==ny+1)
                        ylocright=returnLocation(i,1,z,nx,ny,nz);
                    int ylocleft=returnLocation(i,j-1,z,nx,ny,nz);
                    if(j-1==0)
                        ylocleft=returnLocation(i,ny,z,nx,ny,nz);
                    int zlocright=returnLocation(i,j,z+1,nx,ny,nz);
                    if(z+1==nz)
                        zlocright=returnLocation(i,j,1,nx,ny,nz);
                    int zlocleft=returnLocation(i,j,z-1,nx,ny,nz);
                    if(z-1==0)
                        zlocleft=returnLocation(i,j,nz,nx,ny,nz);
                    a[location][xlocleft]=-c1;
                    a[location][xlocright]=-c1;
                    a[location][ylocleft]=-c2;
                    a[location][ylocright]=-c2;
                    a[location][zlocleft]=-c3;
                    a[location][zlocright]=-c3;
                }
            }
        }
    }
    return a;
}
