//
//  2-2part3.cpp
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
    if(size%2 !=0){
        nth_element (vec.begin(), vec.begin()+(size-1)/2, vec.end());
        return vec[(size-1)/2];
    }
    else{
        nth_element (vec.begin(), vec.begin()+(size-1)/2, vec.end());
        double first=vec[(size-1)/2];
        nth_element (vec.begin(), vec.begin()+(size-1)/2+1, vec.end());
        double second=vec[(size-1)/2+1];
        return (first+second)/2;
    }
}

int main(){
    
    vector<double> myvector={1, 3, -1, 7, 4, 5,22, 33};
    cout<<findMedian(myvector)<<endl;
    cout<<"I believe that is even more efficient as this probably simply utilizes the standard partition algorithm which will run in O(logn) time which is my cheaper than sorting or partial sorting";
}