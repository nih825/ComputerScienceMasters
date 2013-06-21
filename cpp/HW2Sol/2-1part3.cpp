//
//  2-1part3.cpp
//  HW2
//
//  Created by Rukmaiah Bhupalam on 1/19/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <math.h>
using namespace std;

float squareTheValue (float init,const float number) {
    return init+number*number;
}

float squareTheValue1 (float number) {
    return number*number;
}

int main () {
    vector<float> input;
    vector<float> output;
    
    
    for(int i=0; i<10; i++){
        input.push_back((float)rand()/(float)RAND_MAX*10);
    }
    
    output.resize(input.size());
    
    cout<<"Vector Distance: ";
    cout<<sqrt(accumulate(input.begin(),input.end(),0,squareTheValue))<<endl;
    
    
    return 0;
}