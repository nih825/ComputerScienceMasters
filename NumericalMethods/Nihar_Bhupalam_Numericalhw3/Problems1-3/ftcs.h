//
//  ftcs.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/3/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__ftcs__
#define __heatequationsolver__ftcs__

#include <iostream>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;
#endif /* defined(__heatequationsolver__ftcs__) */
vector<vector<vector<double>>> initialize3d(int nx, int ny, int nz, double xsize, double ysize, double zsize,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6);
void printSlice(vector<vector<vector<double>>> array, int i, int ny, int nz);
vector<vector<vector<double>>> initializeSourceVec(double sourcenum, int nx, int ny, int nz);


