//
//  successive_over_relaxation.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 3/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__successive_over_relaxation__
#define __heatequationsolver__successive_over_relaxation__

#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#include "jacobi_iteration.h"
#endif /* defined(__heatequationsolver__successive_over_relaxation__) */
vector<double> sorIteration(vector<double> b, int nx, double dx, double epsilon, double alpha, double dt, int maxIter, double w);

vector<double> sorIteration1step(vector<double> b, vector<double> prevIt, int nx, double dx, double alpha, double dt, double w);
