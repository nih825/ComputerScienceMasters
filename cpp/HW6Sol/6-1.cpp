//
//  6-1.cpp
//  Homework6
//
//  Created by Rukmaiah Bhupalam on 2/17/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
using namespace std;

struct Complex {
public:
    int r;
    int i;
    Complex(int, int);
    Complex operator+(Complex &obj1) const;
    Complex operator*(Complex &obj1) const;
    inline friend ostream& operator<<(ostream &ref, Complex &obj1){
        ref<<obj1.r<<"+"<<obj1.i<<"i";
        return ref;
    }
};

Complex::Complex(int a, int b){
    r=a;
    i=b;
}

Complex Complex::operator+(Complex &obj1) const{
    Complex additive= Complex(r+obj1.r,i+obj1.i);
    return additive;
}

Complex Complex::operator*(Complex &obj1) const{
    int r1=obj1.r;
    int i1=obj1.i;
    int rComp=r*r1+i*i1*-1;
    int iComp=i*r1+i1*r;
    Complex multiplied= Complex(rComp,iComp);
    return multiplied;
}


int main(void){
    Complex first = Complex(3,2);
    Complex second=Complex(2,5);
    Complex add=first+second;
    Complex multiply=first*second;
    cout<<add<<endl;
    cout<<multiply<<endl;
    return 0;
}
