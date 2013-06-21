//
//  gaussian_elim.cpp
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include "gaussian_elim.h"
#include <vector>
#include "float.h"
#include <cmath>
using namespace std;

void printVec(vector<vector<double>> A){
    int n=A.size();
    for(int i=0; i<n; i++){
        cout<<endl;
        for(int j=0;j<n; j++)
            cout<<A[i][j]<<"   ";
    }
    cout<<endl<<endl;
    
}

vector<double> gaussian_elim(vector<vector<double>> A, vector<double> b){
    
    int n=A.size();
    int rowmax;
    
    for(int j=1; j<n; j++){
        
        rowmax=-1;
        double maxvalue=0;
        
        for(int k=j-1;k<n;k++){
            if(abs(A[k][j-1])>maxvalue){
                maxvalue=abs(A[k][j-1]);
                rowmax=k;
            }
        }
        if (rowmax==-1){
            cout<<"Error unable to solve this system, column is all zeros";
            exit(0);
        }
       
        for(int p=0; p<n; p++){
            double temp=A[rowmax][p];
            A[rowmax][p]=A[j-1][p];
            A[j-1][p]=temp;
        }
        double temp=b[rowmax];
        b[rowmax]=b[j-1];
        b[j-1]=temp;
        
        
        for(int i=j; i<n; i++){
            if(A[j-1][j-1]==0){
                cout<<"invalid matrix";
                break;
            }
            double m=A[i][j-1]/A[j-1][j-1];
            for(int k=0;k<n;k++){
                A[i][k]=A[i][k]-A[j-1][k]*m;
            }
            b[i]=b[i]-m*b[j-1];
        }
    }
    
    vector<double> solutions;
    solutions.resize(n);
    solutions[n-1]=b[n-1]/A[n-1][n-1];

    for(int j=n-2; j>=0; j--){
        double val=0;
        for(int i=j+1; i<n; i++){
            val=val+A[j][i]*solutions[i];
        }
        solutions[j]=(b[j]-val)/A[j][j];
    }
    
    return solutions;
    
}
