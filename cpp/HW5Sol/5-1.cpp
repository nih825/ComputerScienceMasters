//
//  5-1.cpp
//  HW5
//
//  Created by Rukmaiah Bhupalam on 2/8/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include<vector>
#include <iostream>
#include <cmath>
using namespace std;

int main(void){
    vector<int> vec={1,22,-21,18,7};
    auto func = [](vector<int> vec) ->vector<int> {
        for(int i=0; i<vec.size()-1; i++)
            for(int j=i+1;j<vec.size();j++){
                if(abs(vec[i])>abs(vec[j])){
                    int temp=vec[i];
                    vec[i]=vec[j];
                    vec[j]=temp;
                }
                    
            }
        return vec;
    };
    vector<int> vec1=func(vec);
    
    for(int i=0; i<vec1.size(); i++)
        cout<<vec1[i]<<endl;
    
}