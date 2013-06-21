//
//  3-2.cpp
//  Homework3
//
//  Created by Rukmaiah Bhupalam on 1/28/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

using namespace std;
#include <iostream>
#include<math.h>
struct Nth_Power {
    Nth_Power(int x) {power=x;}
    int operator()(int i) {
        return pow(i,power);
    }
    private:
        int power;
};

int main()
{
    Nth_Power cube(3);
    for(int i = 1; i < 10; i++) {
        cout<<cube(i)<<endl;
    }
}
