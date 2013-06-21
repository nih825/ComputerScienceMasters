//
//  jacobi_iteration.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/25/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__jacobi_iteration__
#define __heatequationsolver__jacobi_iteration__

#include <iostream>
#include <vector>
using namespace std;

#endif /* defined(__heatequationsolver__jacobi_iteration__) */
int returnLocationJacobi(int i, int j, int k, int nx, int ny, int nz);
vector<vector<vector<double>>> convertTo3dJacobi(vector<double> solution, int nx);
vector<double> createBJacobi(vector<vector<vector<double>>> array,int nx);
vector<double> jacobiIteration1step(vector<double> b, vector<double> prevIt, int nx, double dx, double alpha, double dt);
double findDifference(vector<double> a, vector<double> b, int nx);
vector<double> jacobiIteration(vector<double> b, int nx, double dx, double epsilon, double alpha, double dt, int maxIter);
