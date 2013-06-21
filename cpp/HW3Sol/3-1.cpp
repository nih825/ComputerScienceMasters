//
//  3-1.cpp
//  Homework3
//
//  Created by Rukmaiah Bhupalam on 1/28/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
using namespace std;
struct HelloWorld {
    HelloWorld() { cout << "Hello, world!" << endl;}
};
HelloWorld static_helloworld;
int main()
{
    return 0;
}