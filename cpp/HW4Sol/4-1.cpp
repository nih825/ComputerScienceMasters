//
//  4-1.cpp
//  HW4
//
//  Created by Rukmaiah Bhupalam on 2/2/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//
#include <iostream>
using namespace std;

void g(){
    cout<<"example"<<endl;
}

int h(){
    return -1;
}

int f() {
    cout << "Some text";
    try{
        g();
        cout << h();
    }
    catch(int e){
        cout<<"Error occured"<<endl;
    }
    cout<<"In my simple example this code will work completely fine.  However an error can occur if an error is thrown in one of the functions g or h and then the buffer may not get flushed.  To fix this you can simply wrap each of the functions in a try-catch block.  This same issue can occur with the second example when function f is called which seems like it would result in infinite recursion.  However, if an error is thrown somewhere in f before it is recalled it would end the recursion";

    cout.flush();



    return 0;
}
int main(void){
    f();
    return 0;
}
