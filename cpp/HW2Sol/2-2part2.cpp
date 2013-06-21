//
//  2-2part2.cpp
//  HW2
//
//  Created by Rukmaiah Bhupalam on 1/19/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

double findMedian(vector<double> vec){
    int size=vec.size();
    partial_sort (vec.begin(),vec.begin()+((size-1)/2+2), vec.end());
    
    if(size%2 !=0){
        return vec[(size-1)/2];
    }
    else{
        return (vec[(size-1)/2]+vec[(size-1)/2+1])/2;
    }
}

int main(){
    
    vector<double> myvector={1, 3, -1, 7, 4, 5,22};
    cout<<findMedian(myvector)<<endl;
    cout<<"I believe that this partial sort is going to be more efficient than the full sort as you do not have to sort the entire vector and save operations therefore";
}