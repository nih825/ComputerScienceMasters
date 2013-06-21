//
//  2-1.cpp
//  HW2
//
//  Created by Rukmaiah Bhupalam on 1/19/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

float squareTheValue (float number) {
    return number*number;
}

int main () {
    vector<float> input;
    vector<float> output;
    
    for(int i=0; i<10; i++){
        input.push_back((float)rand()/(float)RAND_MAX*10);
    }
    
    output.resize(input.size());
    transform (input.begin(), input.end(), output.begin(), squareTheValue);
   
    cout << "input:"<<endl;
    for (vector<float>::iterator j=input.begin(); j!=input.end(); ++j)
        cout <<*j<<endl;
    
    cout << "output:"<<endl;
    for (vector<float>::iterator k=output.begin(); k!=output.end(); ++k)
        cout <<*k<<endl;
    
    
    return 0;
}
