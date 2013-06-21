//
//  2-2part4.cpp
//  HW2
//
//  Created by Rukmaiah Bhupalam on 1/19/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <class myType>
myType findMedian(vector<myType> vec){
    int size=vec.size();
    if(size%2 !=0){
        nth_element (vec.begin(), vec.begin()+(size-1)/2, vec.end());
        return vec[(size-1)/2];
    }
    else{
        nth_element (vec.begin(), vec.begin()+(size-1)/2, vec.end());
        myType first=vec[(size-1)/2];
        nth_element (vec.begin(), vec.begin()+(size-1)/2+1, vec.end());
        myType second=vec[(size-1)/2+1];
        return (first+second)/2;
    }
}

int main(){
    
    vector<double> myvector={1, 3, -1, 7, 4, 5,22, 33};
    cout<<findMedian(myvector)<<endl;
}