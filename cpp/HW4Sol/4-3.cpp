//
//  4-3.cpp
//  HW4
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

struct myClass

{
    int var1;
    int var2;
    int funct(int *a){
        return 2;
    }
};

int add(int x, int y){
    
    return x+y;
}

char * charfunct(char * a, char * b){
    return a;
}

int main(void){
    
    
    int *ip = new int;
    
    int i = 5;
    int &ir(i);
    
    double x=5;
    
    myClass testing;
    myClass * a= &testing;
    
    const char charvar='a';
    const char * pointer = &charvar;
    
    
    long arr[]={1,2,3,4,5,6,7,8};
    
    int **var;
    var = new int*[3];
    for(int i = 0; i < 3; i++)
        var[i] = new int[10];
    
    
    int (*functionpointer)(int, int)=&add;
    
    char * (*functionptr1)(char *, char *)=&charfunct;
    
    int myClass::*memberptr = &myClass::var1;
    
    int (myClass::*classfunctionptr)(int *)=&myClass::funct;
    

    
}
