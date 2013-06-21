//
//  GaussSeidel.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 3/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__GaussSeidel__
#define __heatequationsolver__GaussSeidel__

#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#endif /* defined(__heatequationsolver__GaussSeidel__) */
vector<double> gaussSeidelIteration(vector<double> b, int nx, double dx, double epsilon, double alpha, double dt, int maxIter);

vector<double> gaussSeidelIteration1step(vector<double> b, vector<double> prevIt, int nx, double dx, double alpha, double dt);