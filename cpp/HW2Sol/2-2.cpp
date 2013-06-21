#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

double findMedian(vector<double> vec){
    sort (vec.begin(), vec.end());
    int size=vec.size();
    if(size%2 !=0){
        return vec[(size-1)/2];
    }
    else{
        return (vec[(size-1)/2]+vec[(size-1)/2+1])/2;
    }
}

int main(){
    
    vector<double> myvector={1, 3, -1, 7, 4};
    cout<<findMedian(myvector);
}