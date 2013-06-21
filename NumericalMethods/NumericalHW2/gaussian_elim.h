//
//  gaussian_elim.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__gaussian_elim__
#define __heatequationsolver__gaussian_elim__

#include <iostream>
#include <vector>
using namespace std;
void printVec(vector<vector<double>> A);
vector<double> gaussian_elim(vector<vector<double>> A, vector<double> b);


#endif /* defined(__heatequationsolver__gaussian_elim__) */
