//
//  cn.h
//  heatequationsolver
//
//  Created by Rukmaiah Bhupalam on 2/3/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#ifndef __heatequationsolver__cn__
#define __heatequationsolver__cn__

#include <iostream>
#include <vector>
using namespace std;

int returnLocation(int i, int j, int k, int nx, int ny, int nz);
vector<vector<vector<double>>> convertTo3d(vector<double> solution, int nx, int ny, int nz, double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6);
vector<vector<double>> createA(int nx, int ny, int nz, double alpha, double dt, double dx, double dy, double dz,bool wraparound,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6);
vector<double> createB(vector<vector<vector<double>>> array,int nx, int ny, int nz, double alpha, double dt, double dx, double dy, double dz, bool source, vector<vector<vector<double>>> sourceVec,double boundary1, double boundary2, double boundary3, double boundary4, double boundary5, double boundary6);




#endif /* defined(__heatequationsolver__cn__) */
